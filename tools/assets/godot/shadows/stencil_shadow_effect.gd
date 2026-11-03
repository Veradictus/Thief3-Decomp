@tool
extends CompositorEffect

## T3-style stencil shadow volumes, drawn into a per-light screen-space mask.
## T3Shadows (t3_shadows.gd) owns it and puts it on the camera; nothing else
## needs to touch it.
##
## Runs before the opaque pass (the depth prepass is done):
##   1. copies Godot's scene depth into a depth-stencil target of its own
##      (Godot's own stencil is left alone);
##   2. per shadowed light, draws its casters' volumes: z-fail, two-sided
##      stencil with wrap.  Godot uses reverse Z, so the depth test is GREATER;
##   3. resolves: where the stencil is not 0, writes 0 into the light's channel
##      of an RGBA8 mask, and zeroes the stencil for the next light.
## Materials read the mask in light() through the global shader uniforms
## t3_shadow_mask and t3_shadow_depth (t3_lit.gdshaderinc).  One mask holds
## four lights, one per channel.
##
## Needs the Forward+ renderer: without a RenderingDevice (headless, the
## Compatibility renderer) is_supported() is false and nothing is drawn.

# =============================================================================
# VARIABLES
# =============================================================================

## Per-frame input, set by t3_shadows.gd:
## [{'pos': Vector3 (world), 'slot': int 0..3, 'casters': [index into `casters`]}].
var lights: Array = []

## Per-frame input: [{'mesh': int (from add_volume_mesh()), 'xform': Transform3D (world)}].
var casters: Array = []

## Volume draws in the last frame.
var draws := 0

## The rendering device (null without Forward+).
var _rd: RenderingDevice

## Shaders: depth copy, volumes, resolve.
var _sh_copy: RID
var _sh_volume: RID
var _sh_resolve: RID

## Nearest-filter sampler for the depth copy.
var _sampler: RID

## Vertex format of the volume meshes: float position, snorm8 face normal.
var _vformat := -1

## Uploaded volume meshes: [{'va': RID, 'ia': RID, 'count': int, 'bufs': [RID...]}].
var _meshes: Array = []

## The depth-stencil format: D32S8, else D24S8; -1 if neither works.
var _ds_format := -1

## Render targets: the mask, the depth the mask was built against (R32F,
## for the MSAA edge fix in t3_lit), our depth-stencil, and their framebuffer.
var _mask: RID
var _zcopy: RID
var _ds: RID
var _fb: RID

## Size of the render targets, and the render size seen in the last frame.
var _size := Vector2i.ZERO
var _wanted_size := Vector2i.ZERO

## Pipelines: depth copy, volumes, and one resolve per mask channel.
var _pl_copy: RID
var _pl_volume: RID
var _pl_resolve: Array = []

## The mask and depth as textures for the global shader uniforms.
var _mask_tex := Texture2DRD.new()
var _depth_tex := Texture2DRD.new()

## A white texture for the global uniforms while there is no mask.
var _placeholder: ImageTexture

# =============================================================================
# CONSTANTS
# =============================================================================

## The shaders of the three passes.
const COPY_SHADER := 'res://t3_tools/shadows/depth_copy.glsl'
const VOLUME_SHADER := 'res://t3_tools/shadows/volume.glsl'
const RESOLVE_SHADER := 'res://t3_tools/shadows/resolve.glsl'

## Shadowed lights per frame: one per mask channel.
const MAX_LIGHTS := 4

# =============================================================================
# METHODS
# =============================================================================

## Compiles the shaders and makes the sampler and the vertex format.
func _init() -> void:
	effect_callback_type = EFFECT_CALLBACK_TYPE_PRE_OPAQUE
	access_resolved_depth = true
	_rd = RenderingServer.get_rendering_device()
	if _rd == null:
		return

	_sh_copy = _shader(COPY_SHADER)
	_sh_volume = _shader(VOLUME_SHADER)
	_sh_resolve = _shader(RESOLVE_SHADER)
	var ss := RDSamplerState.new()
	ss.min_filter = RenderingDevice.SAMPLER_FILTER_NEAREST
	ss.mag_filter = RenderingDevice.SAMPLER_FILTER_NEAREST
	_sampler = _rd.sampler_create(ss)

	var a0 := RDVertexAttribute.new()
	a0.location = 0
	a0.format = RenderingDevice.DATA_FORMAT_R32G32B32_SFLOAT
	a0.stride = 12
	var a1 := RDVertexAttribute.new()
	a1.location = 1
	a1.format = RenderingDevice.DATA_FORMAT_R8G8B8A8_SNORM
	a1.stride = 4
	_vformat = _rd.vertex_format_create([a0, a1])

	for f in [RenderingDevice.DATA_FORMAT_D32_SFLOAT_S8_UINT, RenderingDevice.DATA_FORMAT_D24_UNORM_S8_UINT]:
		if _rd.texture_is_format_supported_for_usage(f, RenderingDevice.TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT):
			_ds_format = f
			break

	# Until the first mask exists: lit everywhere.  An empty global sampler is
	# not a valid texture for the materials' uniform sets.
	var white := Image.create(1, 1, false, Image.FORMAT_RGBA8)
	white.fill(Color(1, 1, 1, 1))
	_placeholder = ImageTexture.create_from_image(white)
	RenderingServer.global_shader_parameter_set('t3_shadow_mask', _placeholder)
	RenderingServer.global_shader_parameter_set('t3_shadow_depth', _placeholder)

## Whether the effect can draw: Forward+, shaders compiled, a stencil format.
func is_supported() -> bool:
	return _rd != null and _ds_format >= 0 and _sh_copy.is_valid() and _sh_volume.is_valid() \
		and _sh_resolve.is_valid()

## Compiles one .glsl file (imported as RDShaderFile); an invalid RID on error.
func _shader(path: String) -> RID:
	var sf: RDShaderFile = load(path)
	if sf == null:
		push_error('T3 shadows: cannot load %s' % path)
		return RID()

	var spirv := sf.get_spirv()
	for stage in [RenderingDevice.SHADER_STAGE_VERTEX, RenderingDevice.SHADER_STAGE_FRAGMENT]:
		var err := spirv.get_stage_compile_error(stage)
		if err != '':
			push_error('T3 shadows: %s: %s' % [path, err])
			return RID()
	return _rd.shader_create_from_spirv(spirv)

## Uploads a volume mesh as a .t3shadow file stores it (shadow_file.gd): the
## position, normal and index bytes go to the GPU as they are.  Returns the
## mesh index for `casters`, or -1.
func add_volume_mesh(entry: Dictionary) -> int:
	if not is_supported():
		return -1

	var nv := int(entry['vertex_count'])
	var ni := int(entry['index_count'])
	if nv == 0 or ni == 0:
		return -1

	var pos: PackedByteArray = entry['positions']
	var nrm: PackedByteArray = entry['normals']
	var idx: PackedByteArray = entry['indices']
	var wide := int(entry['index_size']) == 4
	var bp := _rd.vertex_buffer_create(pos.size(), pos)
	var bn := _rd.vertex_buffer_create(nrm.size(), nrm)
	var va := _rd.vertex_array_create(nv, _vformat, [bp, bn])
	var ib := _rd.index_buffer_create(ni, RenderingDevice.INDEX_BUFFER_FORMAT_UINT32 if wide
		else RenderingDevice.INDEX_BUFFER_FORMAT_UINT16, idx)
	var ia := _rd.index_array_create(ib, 0, ni)
	_meshes.append({'va': va, 'ia': ia, 'count': ni, 'bufs': [bp, bn, ib]})
	return _meshes.size() - 1

## Number of uploaded volume meshes.
func mesh_count() -> int:
	return _meshes.size()

## Frees the volume meshes `ids` (from add_volume_mesh()); their indices are
## not reused.  Callers stop naming them in `casters` first.
func free_meshes(ids: Array) -> void:
	if _rd == null:
		return
	for id in ids:
		var m: Dictionary = _meshes[id]
		if m.is_empty():
			continue
		_rd.free_rid(m['ia'])
		_rd.free_rid(m['va'])
		for b in m['bufs']:
			_rd.free_rid(b)
		_meshes[id] = {}

## Makes the render targets when the render size has changed.  Call it from
## the main thread between frames (t3_shadows.gd does, every frame): the
## global shader uniforms must not change while a frame is drawn, or the
## materials' uniform sets drawn in it go stale.
func update_targets() -> void:
	if is_supported() and _wanted_size != _size and _wanted_size.x > 0:
		RenderingServer.call_on_render_thread(_make_targets.bind(_wanted_size))

## (Re)makes the render targets for size `s` and points the global shader
## uniforms at them.
func _make_targets(s: Vector2i) -> void:
	# The old targets go after the textures point at the new ones: materials
	# still use them until then.
	var old := [_fb, _mask, _zcopy, _ds]
	var tf := RDTextureFormat.new()
	tf.width = s.x
	tf.height = s.y
	tf.format = RenderingDevice.DATA_FORMAT_R8G8B8A8_UNORM
	tf.usage_bits = RenderingDevice.TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RenderingDevice.TEXTURE_USAGE_SAMPLING_BIT
	_mask = _rd.texture_create(tf, RDTextureView.new())
	tf.format = RenderingDevice.DATA_FORMAT_R32_SFLOAT
	_zcopy = _rd.texture_create(tf, RDTextureView.new())
	var td := RDTextureFormat.new()
	td.width = s.x
	td.height = s.y
	td.format = _ds_format
	td.usage_bits = RenderingDevice.TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
	_ds = _rd.texture_create(td, RDTextureView.new())
	_fb = _rd.framebuffer_create([_mask, _zcopy, _ds])
	_size = s

	_mask_tex.texture_rd_rid = _mask
	RenderingServer.global_shader_parameter_set('t3_shadow_mask', _mask_tex)
	_depth_tex.texture_rd_rid = _zcopy
	RenderingServer.global_shader_parameter_set('t3_shadow_depth', _depth_tex)
	for r in old:
		if r.is_valid():
			_rd.free_rid(r)
	if not _pl_copy.is_valid():
		_make_pipelines(_rd.framebuffer_get_format(_fb))

## Colour writes for the mask channels (r, g, b, a) and the depth copy (z).
func _blend(r: bool, g: bool, b: bool, a: bool, z := false) -> RDPipelineColorBlendState:
	var att := RDPipelineColorBlendStateAttachment.new()
	att.write_r = r
	att.write_g = g
	att.write_b = b
	att.write_a = a
	var att_z := RDPipelineColorBlendStateAttachment.new()
	att_z.write_r = z
	att_z.write_g = z
	att_z.write_b = z
	att_z.write_a = z
	var cb := RDPipelineColorBlendState.new()
	cb.attachments = [att, att_z]
	return cb

## Makes the pipelines of the three passes for framebuffer format `fbf`.
func _make_pipelines(fbf: int) -> void:
	var ms := RDPipelineMultisampleState.new()
	var no_cull := RDPipelineRasterizationState.new()
	no_cull.cull_mode = RenderingDevice.POLYGON_CULL_DISABLED

	# 1. Depth copy: writes depth always, and the R32F copy.
	var d1 := RDPipelineDepthStencilState.new()
	d1.enable_depth_test = true
	d1.enable_depth_write = true
	d1.depth_compare_operator = RenderingDevice.COMPARE_OP_ALWAYS
	_pl_copy = _rd.render_pipeline_create(_sh_copy, fbf, RenderingDevice.INVALID_FORMAT_ID,
		RenderingDevice.RENDER_PRIMITIVE_TRIANGLES, no_cull, ms, d1, _blend(false, false, false, false, true))

	# 2. Volumes: z-fail, two-sided.  Reverse Z: a fragment passes when it is nearer, so GREATER.
	var d2 := RDPipelineDepthStencilState.new()
	d2.enable_depth_test = true
	d2.enable_depth_write = false
	d2.depth_compare_operator = RenderingDevice.COMPARE_OP_GREATER
	d2.enable_stencil = true
	for side in ['front', 'back']:
		d2.set(side + '_op_compare', RenderingDevice.COMPARE_OP_ALWAYS)
		d2.set(side + '_op_compare_mask', 0xFF)
		d2.set(side + '_op_write_mask', 0xFF)
		d2.set(side + '_op_fail', RenderingDevice.STENCIL_OP_KEEP)
		d2.set(side + '_op_pass', RenderingDevice.STENCIL_OP_KEEP)
	d2.front_op_depth_fail = RenderingDevice.STENCIL_OP_DECREMENT_AND_WRAP
	d2.back_op_depth_fail = RenderingDevice.STENCIL_OP_INCREMENT_AND_WRAP
	_pl_volume = _rd.render_pipeline_create(_sh_volume, fbf, _vformat, RenderingDevice.RENDER_PRIMITIVE_TRIANGLES,
		no_cull, ms, d2, _blend(false, false, false, false))

	# 3. Resolve: where the stencil is not 0, write 0 to one channel and zero the stencil.
	var d3 := RDPipelineDepthStencilState.new()
	d3.enable_depth_test = false
	d3.enable_stencil = true
	for side in ['front', 'back']:
		d3.set(side + '_op_compare', RenderingDevice.COMPARE_OP_NOT_EQUAL)
		d3.set(side + '_op_reference', 0)
		d3.set(side + '_op_compare_mask', 0xFF)
		d3.set(side + '_op_write_mask', 0xFF)
		d3.set(side + '_op_fail', RenderingDevice.STENCIL_OP_KEEP)
		d3.set(side + '_op_depth_fail', RenderingDevice.STENCIL_OP_KEEP)
		d3.set(side + '_op_pass', RenderingDevice.STENCIL_OP_ZERO)
	_pl_resolve.clear()
	for ch in MAX_LIGHTS:
		_pl_resolve.append(_rd.render_pipeline_create(_sh_resolve, fbf, RenderingDevice.INVALID_FORMAT_ID,
			RenderingDevice.RENDER_PRIMITIVE_TRIANGLES, no_cull, ms, d3,
			_blend(ch == 0, ch == 1, ch == 2, ch == 3)))

## A Transform3D as a column-major mat4, for the push constant.
static func _mat4(t: Transform3D) -> PackedFloat32Array:
	var b := t.basis
	return PackedFloat32Array([b.x.x, b.x.y, b.x.z, 0.0, b.y.x, b.y.y, b.y.z, 0.0,
		b.z.x, b.z.y, b.z.z, 0.0, t.origin.x, t.origin.y, t.origin.z, 1.0])

## Builds the mask for this frame from `lights` and `casters`.
func _render_callback(_type: int, data: RenderData) -> void:
	if not is_supported():
		return

	var rsb: RenderSceneBuffersRD = data.get_render_scene_buffers()
	var scene: RenderSceneDataRD = data.get_render_scene_data()
	var s := rsb.get_internal_size()
	# A new size waits for update_targets(); the mask keeps its last contents.
	_wanted_size = s
	if s.x == 0 or s.y == 0 or s != _size:
		return

	# With MSAA, the resolved depth: one depth per pixel (see the edge fix in t3_lit).
	var depth: RID
	if rsb.get_msaa_3d() != RenderingServer.VIEWPORT_MSAA_DISABLED:
		depth = rsb.get_texture('render_buffers', 'depth')
	else:
		depth = rsb.get_depth_layer(0)
	var u := RDUniform.new()
	u.uniform_type = RenderingDevice.UNIFORM_TYPE_SAMPLER_WITH_TEXTURE
	u.binding = 0
	u.add_id(_sampler)
	u.add_id(depth)
	var set_copy := UniformSetCacheRD.get_cache(_sh_copy, 0, [u])
	var ub := RDUniform.new()
	ub.uniform_type = RenderingDevice.UNIFORM_TYPE_UNIFORM_BUFFER
	ub.binding = 0
	ub.add_id(scene.get_uniform_buffer())
	var set_scene := UniformSetCacheRD.get_cache(_sh_volume, 0, [ub])
	var view := scene.get_cam_transform().affine_inverse()

	# The mask clears to 1 (lit everywhere).
	var dl := _rd.draw_list_begin(_fb, RenderingDevice.DRAW_CLEAR_ALL,
		PackedColorArray([Color(1, 1, 1, 1), Color(0, 0, 0, 0)]), 0.0, 0)
	_rd.draw_list_bind_render_pipeline(dl, _pl_copy)
	_rd.draw_list_bind_uniform_set(dl, set_copy, 0)
	_rd.draw_list_draw(dl, false, 1, 3)
	var n := 0
	for l in lights:
		var lp: Vector3 = view * (l['pos'] as Vector3)
		_rd.draw_list_bind_render_pipeline(dl, _pl_volume)
		_rd.draw_list_bind_uniform_set(dl, set_scene, 0)
		for ci in l['casters']:
			var c: Dictionary = casters[ci]
			var m: Dictionary = _meshes[c['mesh']]
			var pc := _mat4(view * (c['xform'] as Transform3D))
			pc.append_array(PackedFloat32Array([lp.x, lp.y, lp.z, 1.0]))
			_rd.draw_list_bind_vertex_array(dl, m['va'])
			_rd.draw_list_bind_index_array(dl, m['ia'])
			_rd.draw_list_set_push_constant(dl, pc.to_byte_array(), pc.size() * 4)
			_rd.draw_list_draw(dl, true, 1)
			n += 1
		_rd.draw_list_bind_render_pipeline(dl, _pl_resolve[int(l['slot']) % MAX_LIGHTS])
		_rd.draw_list_draw(dl, false, 1, 3)
	_rd.draw_list_end()
	draws = n

## Frees the GPU resources; the effect draws nothing afterwards.  T3Shadows
## calls it when it leaves the tree, before the RenderingDevice goes.
func release() -> void:
	if _rd == null:
		return

	# Materials that outlive the effect must not keep the freed targets.
	RenderingServer.global_shader_parameter_set('t3_shadow_mask', _placeholder)
	RenderingServer.global_shader_parameter_set('t3_shadow_depth', _placeholder)
	for m in _meshes:
		if not m.is_empty():
			_rd.free_rid(m['ia'])
			_rd.free_rid(m['va'])
			for b in m['bufs']:
				_rd.free_rid(b)
	_meshes.clear()
	# Freeing a shader frees the pipelines made from it.
	for r in [_fb, _mask, _zcopy, _ds, _sampler, _sh_copy, _sh_volume, _sh_resolve]:
		if r.is_valid():
			_rd.free_rid(r)
	_rd = null

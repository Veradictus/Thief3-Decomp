extends RefCounted

## Ray picking over a loaded map without physics bodies.
##
## Meshes: a ray/AABB test on every indexed MeshInstance3D, then exact
## ray/triangle tests on the candidates, nearest first.  Triangle lists are
## read once per Mesh resource (per surface, so the hit surface and its
## material are known) and cached.
## Markers (nodes without geometry, e.g. player starts, AI points, lights):
## the nearest one within a small radius of the ray.
##
## pick() returns {} or {node, position, distance, kind ("mesh"|"marker"),
## surface (mesh hits)}.

# =============================================================================
# VARIABLES
# =============================================================================

## Meshes indexed for picking and world_bounds().
var meshes: Array[MeshInstance3D] = []

## Markers (geometry-less actors) indexed for picking.
var markers: Array[Node3D] = []

## Marker pick radius in metres; grows slowly with distance so distant
## markers are still easy to click.
var marker_radius := 0.3

## Cache: Mesh -> Array[PackedVector3Array], one array per surface.
var _triangles := {}

# =============================================================================
# METHODS
# =============================================================================

## Indexes every MeshInstance3D under `root` for picking and world_bounds().
## A node is left out when `skip` is given and returns true for it.
func index_meshes(root: Node, skip: Callable = Callable()) -> void:
	meshes.clear()
	for n in root.find_children('*', 'MeshInstance3D', true, false):
		if skip.is_valid() and skip.call(n):
			continue
		meshes.append(n)

## Picks under the camera at `screen_pos` (viewport pixels). Set
## `include_markers` to false to hit only meshes.
func pick(camera: Camera3D, screen_pos: Vector2, include_markers: bool = true) -> Dictionary:
	var origin := camera.project_ray_origin(screen_pos)
	var dir := camera.project_ray_normal(screen_pos)
	return pick_ray(origin, dir, include_markers)

## Picks the nearest mesh (by ray/triangle test) or marker (by proximity to
## the ray) along the ray from `origin` in direction `dir`. Returns {} for no hit.
func pick_ray(origin: Vector3, dir: Vector3, include_markers: bool = true) -> Dictionary:
	var best := {}
	var best_d := INF
	var candidates: Array = []

	for mi in meshes:
		if not is_instance_valid(mi) or mi.mesh == null or not mi.is_visible_in_tree():
			continue

		var box := mi.global_transform * mi.get_aabb()
		var enter = box.intersects_ray(origin, dir)
		if enter == null:
			if not box.has_point(origin):
				continue
			# The ray starts inside the box.
			enter = origin

		candidates.append([origin.distance_to(enter), mi])

	candidates.sort_custom(func(a, b): return a[0] < b[0])
	for c in candidates:
		# Sorted by entry distance, so nothing further can beat the best hit so far.
		if c[0] > best_d:
			break

		var hit := ray_mesh(c[1], origin, dir)
		if not hit.is_empty() and hit['distance'] < best_d:
			best_d = hit['distance']
			best = hit

	if include_markers:
		for m in markers:
			if not is_instance_valid(m) or not m.is_visible_in_tree():
				continue

			var p := m.global_position
			var t := (p - origin).dot(dir)

			# Behind the camera, or already beaten by a closer hit.
			if t <= 0.0 or t >= best_d:
				continue

			if (origin + dir * t).distance_to(p) <= maxf(marker_radius, t * 0.012):
				best_d = t
				best = {'node': m, 'position': p, 'distance': t, 'kind': 'marker'}

	return best

## Exact ray/triangle test against `mi`'s surfaces, falling back to its AABB
## when no CPU-side triangles are available.
func ray_mesh(mi: MeshInstance3D, origin: Vector3, dir: Vector3) -> Dictionary:
	var xf := mi.global_transform
	var inv := xf.affine_inverse()
	var lo := inv * origin
	var ld := inv.basis * dir
	var best_d := INF
	var best := {}
	var surfaces := surface_triangles(mi.mesh)
	var has_triangles := false

	for s in surfaces.size():
		var tri: PackedVector3Array = surfaces[s]

		# An empty/degenerate surface leaves this false, triggering the fallback below.
		if tri.size() >= 3:
			has_triangles = true

		var i := 0
		var n := tri.size() - 2
		while i < n:
			var p = Geometry3D.ray_intersects_triangle(lo, ld, tri[i], tri[i + 1], tri[i + 2])
			if p != null:
				var wp: Vector3 = xf * p
				var d := origin.distance_to(wp)
				if d < best_d:
					best_d = d
					best = {'node': mi, 'position': wp, 'distance': d, 'kind': 'mesh', 'surface': s}
			i += 3

	# No CPU-side triangles (e.g. a renderer without mesh read-back): fall back to the box.
	if best.is_empty() and not has_triangles:
		var box := xf * mi.get_aabb()
		var enter = box.intersects_ray(origin, dir)
		if enter != null:
			best = {'node': mi, 'position': enter, 'distance': origin.distance_to(enter), 'kind': 'mesh', 'surface': 0}

	return best

## Each surface's triangles as flat vertex lists, in mesh-local space
## (indices expanded), cached per Mesh resource.
func surface_triangles(mesh: Mesh) -> Array:
	if _triangles.has(mesh):
		return _triangles[mesh]

	var out: Array = []
	for s in mesh.get_surface_count():
		# Only triangle-list surfaces are picked.
		if mesh.surface_get_primitive_type(s) != Mesh.PRIMITIVE_TRIANGLES:
			out.append(PackedVector3Array())
			continue

		var arrays := mesh.surface_get_arrays(s)

		# No CPU-side vertex data for this surface.
		if arrays.is_empty() or arrays[Mesh.ARRAY_VERTEX] == null:
			out.append(PackedVector3Array())
			continue

		var verts: PackedVector3Array = arrays[Mesh.ARRAY_VERTEX]
		var tri := PackedVector3Array()
		var idx = arrays[Mesh.ARRAY_INDEX]
		if idx is PackedInt32Array and not idx.is_empty():
			# Expand the index buffer into a flat triangle list.
			tri.resize(idx.size())
			for k in idx.size():
				tri[k] = verts[idx[k]]
		else:
			# Already a flat triangle list.
			tri = verts
		out.append(tri)

	_triangles[mesh] = out
	return out

## Bounding box of everything under `node`, in the node's own space.
static func local_bounds(node: Node3D) -> AABB:
	var inv := node.global_transform.affine_inverse()
	var box := AABB()
	var have := false
	var nodes: Array = [node]
	nodes.append_array(node.find_children('*', 'VisualInstance3D', true, false))

	for n in nodes:
		if not (n is VisualInstance3D) or not (n as VisualInstance3D).is_visible_in_tree():
			continue

		# Gizmos aren't part of the actor's own geometry.
		if n.has_meta('t3_gizmo'):
			continue

		var b: AABB = (inv * (n as VisualInstance3D).global_transform) * (n as VisualInstance3D).get_aabb()
		box = b if not have else box.merge(b)
		have = true

	# A marker still needs a small box to select and focus on.
	if not have:
		box = AABB(Vector3(-0.15, -0.15, -0.15), Vector3(0.3, 0.3, 0.3))

	return box

## World-space bounds of all indexed meshes (for placing the camera).
func world_bounds() -> AABB:
	var box := AABB()
	var have := false

	for mi in meshes:
		if not is_instance_valid(mi) or not mi.is_visible_in_tree():
			continue
		var b := mi.global_transform * mi.get_aabb()
		box = b if not have else box.merge(b)
		have = true

	return box

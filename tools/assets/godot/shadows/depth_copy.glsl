#[vertex]
#version 450
// A fullscreen triangle.
void main() {
	vec2 p = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
	gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);
}
#[fragment]
#version 450
// Copies Godot's scene depth (single-sample or resolved) into the effect's own
// depth-stencil target, and into an R32F texture for the MSAA edge fix.
layout(set = 0, binding = 0) uniform sampler2D scene_depth;
layout(location = 0) out vec4 frag;     // the mask: masked off
layout(location = 1) out vec4 frag_z;
void main() {
	float d = texelFetch(scene_depth, ivec2(gl_FragCoord.xy), 0).r;
	gl_FragDepth = d;
	frag = vec4(1.0);
	frag_z = vec4(d);
}

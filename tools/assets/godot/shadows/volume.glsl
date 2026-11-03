#[vertex]
#version 450
// A T3 shadow-volume mesh (.t3shadow): every face has its own 3 vertices
// carrying the face normal, plus a degenerate quad on every edge.  Vertices of
// light-facing faces go to infinity (w = 0), so the faces turned away from the
// light are the near cap, the light-facing faces the far cap, and the edge
// quads on the silhouette the sides.  The volume is closed, so z-fail works.
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec4 in_face_normal;   // snorm8, w unused
layout(set = 0, binding = 0, std140) uniform SceneDataBlock {
	mat4 projection_matrix;      // Godot's own (reverse Z, flip corrections included)
	mat4 inv_projection_matrix;
} scene;
layout(push_constant, std430) uniform Params {
	mat4 modelview;   // caster -> camera view space
	vec4 light_pos;   // view space
} pc;
void main() {
	vec3 p = (pc.modelview * vec4(in_pos, 1.0)).xyz;
	vec3 n = mat3(pc.modelview) * in_face_normal.xyz;
	if (dot(n, pc.light_pos.xyz - p) > 0.0) {
		vec4 c = scene.projection_matrix * vec4(p - pc.light_pos.xyz, 0.0);
		c.z = 0.0;   // reverse-Z far plane at infinity: depth 0, never clipped
		gl_Position = c;
	} else {
		gl_Position = scene.projection_matrix * vec4(p, 1.0);
	}
}
#[fragment]
#version 450
layout(location = 0) out vec4 frag;
layout(location = 1) out vec4 frag_z;   // colour writes are masked off; the pipeline needs the outputs
void main() {
	frag = vec4(0.0);
	frag_z = vec4(0.0);
}

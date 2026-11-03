#[vertex]
#version 450
// A fullscreen triangle.
void main() {
	vec2 p = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
	gl_Position = vec4(p * 2.0 - 1.0, 0.0, 1.0);
}
#[fragment]
#version 450
// Runs where the stencil is not 0 (in shadow): writes 0 into this light's
// channel of the mask (the pipeline picks the channel) and zeroes the stencil.
layout(location = 0) out vec4 frag;
layout(location = 1) out vec4 frag_z;
void main() {
	frag = vec4(0.0);
	frag_z = vec4(0.0);
}

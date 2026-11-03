shader_type spatial;
// Alpha-tested surfaces (glTF alphaMode MASK) lit with T3's stencil shadows;
// see t3_lit.gdshaderinc.
#define T3_ALPHA_SCISSOR
#include "res://t3_tools/shadows/t3_lit.gdshaderinc"

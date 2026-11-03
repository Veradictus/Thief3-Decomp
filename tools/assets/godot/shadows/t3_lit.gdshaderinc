// Per-pixel lighting with T3's stencil shadows: the body of t3_lit.gdshader
// and t3_lit_masked.gdshader (which defines T3_ALPHA_SCISSOR first).
//
// T3Shadows (t3_shadows.gd) puts this material in place of a map's
// StandardMaterial3Ds and copies their settings; stencil_shadow_effect.gd
// builds the shadow mask.  light() is Godot's default lighting (Burley
// diffuse, Schlick-GGX specular), so a converted material looks as before,
// times the light's mask channel.
//
// Which channel a light uses travels in its specular amount.  T3Shadows
// draws a light with a channel through a stand-in light of its own that only
// lights t3_lit surfaces, whose specular is the light's own plus
// 32 * (channel + 1).  A real light's specular stays below 16, so light()
// tells them apart and takes the stand-in's value apart again.

global uniform sampler2D t3_shadow_mask : filter_nearest;
global uniform sampler2D t3_shadow_depth : filter_nearest;

uniform vec4 albedo : source_color = vec4(1.0);
uniform sampler2D albedo_texture : source_color, hint_default_white, filter_linear_mipmap, repeat_enable;
uniform bool use_vertex_color = false;
uniform bool vertex_color_srgb = false;
uniform sampler2D normal_texture : hint_normal, filter_linear_mipmap, repeat_enable;
uniform float normal_scale = 1.0;
uniform vec3 emission : source_color = vec3(0.0);
uniform sampler2D emission_texture : source_color, hint_default_white, filter_linear_mipmap, repeat_enable;
uniform float emission_energy = 1.0;
uniform float roughness : hint_range(0.0, 1.0) = 1.0;
uniform float metallic : hint_range(0.0, 1.0) = 0.0;
uniform float specular : hint_range(0.0, 1.0) = 0.5;
uniform vec3 uv1_scale = vec3(1.0);
uniform vec3 uv1_offset = vec3(0.0);
uniform float alpha_scissor_threshold = 0.5;
// MSAA: the mask is per pixel, built against one depth per pixel.  At an edge
// that depth can belong to another surface, so take the mask of the
// neighbour (of 5) whose depth matches this fragment best.
uniform bool edge_fix = true;

varying vec2 mask_px;

void vertex() {
	UV = UV * uv1_scale.xy + uv1_offset.xy;
}

void fragment() {
	vec4 c = albedo * texture(albedo_texture, UV);
	if (use_vertex_color) {
		vec3 vc = COLOR.rgb;
		if (vertex_color_srgb) {
			vc = mix(pow((vc + vec3(0.055)) * (1.0 / 1.055), vec3(2.4)), vc * (1.0 / 12.92), lessThan(vc, vec3(0.04045)));
		}
		c *= vec4(vc, COLOR.a);
	}
	ALBEDO = c.rgb;
#ifdef T3_ALPHA_SCISSOR
	ALPHA = c.a;
	ALPHA_SCISSOR_THRESHOLD = alpha_scissor_threshold;
#endif
	NORMAL_MAP = texture(normal_texture, UV).rgb;
	NORMAL_MAP_DEPTH = normal_scale;
	EMISSION = emission * texture(emission_texture, UV).rgb * emission_energy;
	ROUGHNESS = roughness;
	METALLIC = metallic;
	SPECULAR = specular;

	ivec2 px = ivec2(FRAGCOORD.xy);
	ivec2 best = px;
	if (edge_fix) {
		float z = FRAGCOORD.z;
		float bd = abs(texelFetch(t3_shadow_depth, px, 0).r - z);
		ivec2 offs[4] = { ivec2(1, 0), ivec2(-1, 0), ivec2(0, 1), ivec2(0, -1) };
		ivec2 lim = ivec2(VIEWPORT_SIZE) - 1;
		for (int i = 0; i < 4; i++) {
			ivec2 q = clamp(px + offs[i], ivec2(0), lim);
			float d = abs(texelFetch(t3_shadow_depth, q, 0).r - z);
			if (d < bd * 0.5) {
				bd = d;
				best = q;
			}
		}
	}
	mask_px = vec2(best) + 0.5;
}

float t3_schlick(float u) {
	float m = 1.0 - u;
	float m2 = m * m;
	return m2 * m2 * m;
}

void light() {
	// Omni and spot lights pass twice their specular; see the top of this file.
	float amount = SPECULAR_AMOUNT;
	float lit = 1.0;
	float s = SPECULAR_AMOUNT * 0.5;
	if (!LIGHT_IS_DIRECTIONAL && s >= 16.0) {
		int k = int(floor(s / 32.0));
		int slot = k - 1;
		amount = (s - 32.0 * float(k)) * 2.0;
		if (slot >= 0 && slot < 4) {
			vec4 m = texelFetch(t3_shadow_mask, ivec2(mask_px), 0);
			// no dynamic vector indexing: it does not compile everywhere
			lit = slot == 0 ? m.r : slot == 1 ? m.g : slot == 2 ? m.b : m.a;
		}
	}

	// Godot's default BRDF (scene_forward_lights_inc.glsl, light_compute()).
	vec3 H = normalize(VIEW + LIGHT);
	float NdotL = min(dot(NORMAL, LIGHT), 1.0);
	float cNdotL = max(NdotL, 0.0);
	float cNdotV = max(dot(NORMAL, VIEW), 1e-4);
	float cLdotH = clamp(dot(LIGHT, H), 0.0, 1.0);
	float cNdotH = clamp(dot(NORMAL, H), 0.0, 1.0);
	float rough = ROUGHNESS;
	vec3 radiance = LIGHT_COLOR * ATTENUATION * lit;
	if (METALLIC < 1.0) {
		float fd90 = 2.0 * cLdotH * cLdotH * rough - 0.5;
		float diffuse = (1.0 / PI) * (1.0 + fd90 * t3_schlick(cNdotV)) * (1.0 + fd90 * t3_schlick(cNdotL)) * cNdotL;
		// Godot multiplies DIFFUSE_LIGHT by the albedo afterwards.
		DIFFUSE_LIGHT += radiance * diffuse;
	}
	if (rough > 0.0) {
		float a = rough * rough;
		float ah = cNdotH * a;
		float k = a / (1.0 - cNdotH * cNdotH + ah * ah);
		float D = clamp(k * k * (1.0 / PI), 0.0, 65504.0);
		float G = clamp(0.5 / mix(2.0 * cNdotL * cNdotV, cNdotL + cNdotV, a), 0.0, 65504.0);
		vec3 f0 = mix(vec3(0.16 * specular * specular), ALBEDO, METALLIC);
		float f90 = clamp(dot(f0, vec3(50.0 * 0.33)), METALLIC, 1.0);
		vec3 F = f0 + (f90 - f0) * t3_schlick(cLdotH);
		SPECULAR_LIGHT += cNdotL * D * F * G * radiance * amount;
	}
}

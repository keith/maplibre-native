// Generated code, do not modify this file!
#pragma once
#include <mbgl/shaders/shader_source.hpp>

namespace mbgl {
namespace shaders {

template <>
struct ShaderSource<BuiltIn::FillPatternShader, gfx::Backend::Type::OpenGL> {
    static constexpr const char* name = "FillPatternShader";
    static constexpr const char* vertex = R"(layout (std140) uniform FillPatternDrawableUBO {
    highp mat4 u_matrix;
    highp vec4 u_scale;
    highp vec2 u_pixel_coord_upper;
    highp vec2 u_pixel_coord_lower;
    highp vec2 u_texsize;
    highp float pad1;
    highp float pad2;
};
layout (std140) uniform FillPatternEvaluatedPropsUBO {
    highp float u_opacity;
    highp float u_fade;
    highp float padding_props1;
    highp float padding_props2;
};
layout (std140) uniform FillPatternInterpolateUBO {
    highp float u_pattern_from_t;
    highp float u_pattern_to_t;
    highp float u_opacity_t;
    highp float u_padding_interp1;
};
layout (std140) uniform FillPatternTilePropsUBO {
    highp vec4 u_pattern_from;
    highp vec4 u_pattern_to;
};

layout (location = 0) in vec2 a_pos;

out vec2 v_pos_a;
out vec2 v_pos_b;

#ifndef HAS_UNIFORM_u_opacity
layout (location = 1) in lowp vec2 a_opacity;
out lowp float opacity;
#endif
#ifndef HAS_UNIFORM_u_pattern_from
layout (location = 2) in lowp vec4 a_pattern_from;
out lowp vec4 pattern_from;
#endif
#ifndef HAS_UNIFORM_u_pattern_to
layout (location = 3) in lowp vec4 a_pattern_to;
out lowp vec4 pattern_to;
#endif

void main() {
    #ifndef HAS_UNIFORM_u_opacity
opacity = unpack_mix_vec2(a_opacity, u_opacity_t);
#else
lowp float opacity = u_opacity;
#endif
    #ifndef HAS_UNIFORM_u_pattern_from
pattern_from = a_pattern_from;
#else
mediump vec4 pattern_from = u_pattern_from;
#endif
    #ifndef HAS_UNIFORM_u_pattern_to
pattern_to = a_pattern_to;
#else
mediump vec4 pattern_to = u_pattern_to;
#endif

    vec2 pattern_tl_a = pattern_from.xy;
    vec2 pattern_br_a = pattern_from.zw;
    vec2 pattern_tl_b = pattern_to.xy;
    vec2 pattern_br_b = pattern_to.zw;

    float pixelRatio = u_scale.x;
    float tileZoomRatio = u_scale.y;
    float fromScale = u_scale.z;
    float toScale = u_scale.w;

    vec2 display_size_a = vec2((pattern_br_a.x - pattern_tl_a.x) / pixelRatio, (pattern_br_a.y - pattern_tl_a.y) / pixelRatio);
    vec2 display_size_b = vec2((pattern_br_b.x - pattern_tl_b.x) / pixelRatio, (pattern_br_b.y - pattern_tl_b.y) / pixelRatio);
    gl_Position = u_matrix * vec4(a_pos, 0, 1);

    v_pos_a = get_pattern_pos(u_pixel_coord_upper, u_pixel_coord_lower, fromScale * display_size_a, tileZoomRatio, a_pos);
    v_pos_b = get_pattern_pos(u_pixel_coord_upper, u_pixel_coord_lower, toScale * display_size_b, tileZoomRatio, a_pos);
}
)";
    static constexpr const char* fragment = R"(layout (std140) uniform FillPatternDrawableUBO {
    highp mat4 u_matrix;
    highp vec4 u_scale;
    highp vec2 u_pixel_coord_upper;
    highp vec2 u_pixel_coord_lower;
    highp vec2 u_texsize;
    highp float pad1;
    highp float pad2;
};
layout (std140) uniform FillPatternEvaluatedPropsUBO {
    highp float u_opacity;
    highp float u_fade;
    highp float padding_props1;
    highp float padding_props2;
};
layout (std140) uniform FillPatternInterpolateUBO {
    highp float u_pattern_from_t;
    highp float u_pattern_to_t;
    highp float u_opacity_t;
    highp float u_padding_interp1;
};
layout (std140) uniform FillPatternTilePropsUBO {
    highp vec4 u_pattern_from;
    highp vec4 u_pattern_to;
};

uniform sampler2D u_image;

in vec2 v_pos_a;
in vec2 v_pos_b;

#ifndef HAS_UNIFORM_u_opacity
in lowp float opacity;
#endif
#ifndef HAS_UNIFORM_u_pattern_from
in lowp vec4 pattern_from;
#endif
#ifndef HAS_UNIFORM_u_pattern_to
in lowp vec4 pattern_to;
#endif

void main() {
    #ifdef HAS_UNIFORM_u_opacity
lowp float opacity = u_opacity;
#endif
    #ifdef HAS_UNIFORM_u_pattern_from
mediump vec4 pattern_from = u_pattern_from;
#endif
    #ifdef HAS_UNIFORM_u_pattern_to
mediump vec4 pattern_to = u_pattern_to;
#endif

    vec2 pattern_tl_a = pattern_from.xy;
    vec2 pattern_br_a = pattern_from.zw;
    vec2 pattern_tl_b = pattern_to.xy;
    vec2 pattern_br_b = pattern_to.zw;

    if (u_texsize.x < 1.0 || u_texsize.y < 1.0) {
        discard;
    }

    vec2 imagecoord = mod(v_pos_a, 1.0);
    vec2 pos = mix(pattern_tl_a / u_texsize, pattern_br_a / u_texsize, imagecoord);
    vec4 color1 = texture(u_image, pos);

    vec2 imagecoord_b = mod(v_pos_b, 1.0);
    vec2 pos2 = mix(pattern_tl_b / u_texsize, pattern_br_b / u_texsize, imagecoord_b);
    vec4 color2 = texture(u_image, pos2);

    fragColor = mix(color1, color2, u_fade) * opacity;

#ifdef OVERDRAW_INSPECTOR
    fragColor = vec4(1.0);
#endif
}
)";
};

} // namespace shaders
} // namespace mbgl

#version 150

precision mediump float;
uniform vec4 tgfx_RTAdjust;
uniform mat3 Matrix_P0;

in vec2 aPosition;

void main() {
    // Processor0 : DefaultGeometryProcessor
    vec2 position = (Matrix_P0 * vec3(aPosition, 1.0)).xy;
    gl_Position = vec4(position.xy * tgfx_RTAdjust.xz + tgfx_RTAdjust.yw, 0, 1);
}
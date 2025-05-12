#version 400

uniform vec4 sk_RTAdjust;
in vec2 inPosition;
void main() {
    vec2 _tmp_1_inPosition = inPosition;
    gl_Position = vec4(_tmp_1_inPosition, 0.0, 1.0);
    gl_Position = vec4(gl_Position.xy * sk_RTAdjust.xz + gl_Position.ww * sk_RTAdjust.yw, 0.0, gl_Position.w);
}
#version 400

uniform vec4 sk_RTAdjust;
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec4 inColor;
in vec4 inCircleEdge;
noperspective out vec4 vinCircleEdge_S0;
noperspective out vec4 vinColor_S0;
void main() {
    vinCircleEdge_S0 = inCircleEdge;
    vinColor_S0 = inColor;
    vec2 _tmp_0_inPosition = inPosition;
    gl_Position = vec4(_tmp_0_inPosition, 0.0, 1.0);
    gl_Position = vec4(gl_Position.xy * sk_RTAdjust.xz + gl_Position.ww * sk_RTAdjust.yw, 0.0, gl_Position.w);
}


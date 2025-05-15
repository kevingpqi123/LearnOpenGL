#version 400

uniform vec4 sk_RTAdjust;
in vec2 inPosition;
in vec4 sk_Color;
in vec2 inEllipseOffset;
in vec4 inEllipseRadii;
noperspective out vec2 vEllipseOffsets_S0;
noperspective out vec4 vEllipseRadii_S0;
noperspective out vec4 vinColor_S0;
void main() {
    vEllipseOffsets_S0 = inEllipseOffset;
    vEllipseRadii_S0 = inEllipseRadii;
    vinColor_S0 = sk_Color;
    vec2 _tmp_0_inPosition = inPosition;
    gl_Position = vec4(_tmp_0_inPosition, 0.0, 1.0);
    gl_Position = vec4(gl_Position.xy * sk_RTAdjust.xz + gl_Position.ww * sk_RTAdjust.yw, 0.0, gl_Position.w);
}

#version 150

precision mediump float;
uniform vec4 tgfx_RTAdjust;

in vec2 inPosition;
in vec2 inEllipseOffset;
in vec4 inEllipseRadii;

out vec2 EllipseOffsets_P0;
out vec4 EllipseRadii_P0;

void main() {
    // Processor0 : EllipseGeometryProcessor
    EllipseOffsets_P0 = inEllipseOffset;
    EllipseRadii_P0 = inEllipseRadii;
    gl_Position = vec4(inPosition.xy * tgfx_RTAdjust.xz + tgfx_RTAdjust.yw, 0, 1);
}
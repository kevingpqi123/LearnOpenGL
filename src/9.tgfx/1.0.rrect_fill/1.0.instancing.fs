#version 150

precision mediump float;
uniform vec4 Color_P0;

in highp vec2 EllipseOffsets_P0;
in highp vec4 EllipseRadii_P0;

out vec4 tgfx_FragColor;

void main() {
    vec4 outputColor_P0;
    vec4 outputCoverage_P0;
    { // Processor0 : EllipseGeometryProcessor
        outputColor_P0 = Color_P0;
        vec2 offset = EllipseOffsets_P0.xy;
        float test = dot(offset, offset) - 1.0;
        vec2 grad = 2.0*offset*EllipseRadii_P0.xy;
        float grad_dot = dot(grad, grad);
        grad_dot = max(grad_dot, 1.1755e-38);
        float invlen = inversesqrt(grad_dot);
        float edgeAlpha = clamp(0.5-test*invlen, 0.0, 1.0);
        outputCoverage_P0 = vec4(edgeAlpha);
    }
    { // Processor1 : EmptyXferProcessor
        tgfx_FragColor = outputColor_P0 * outputCoverage_P0;
    }
}

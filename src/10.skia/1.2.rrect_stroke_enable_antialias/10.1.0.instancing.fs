#version 400

out vec4 sk_FragColor;
noperspective in vec2 vEllipseOffsets_S0;
noperspective in vec4 vEllipseRadii_S0;
noperspective in vec4 vinColor_S0;
void main() {
    vec4 outputColor_S0 = vinColor_S0;
    vec2 offset = vEllipseOffsets_S0;
    offset *= vEllipseRadii_S0.xy;
    float test = dot(offset, offset) - 1.0;
    vec2 grad = (2.0 * offset) * vEllipseRadii_S0.xy;
    float grad_dot = dot(grad, grad);
    grad_dot = max(grad_dot, 1.1755e-38);
    float invlen = inversesqrt(grad_dot);
    float edgeAlpha = clamp(0.5 - test * invlen, 0.0, 1.0);
    offset = vEllipseOffsets_S0 * vEllipseRadii_S0.zw;
    test = dot(offset, offset) - 1.0;
    grad = (2.0 * offset) * vEllipseRadii_S0.zw;
    grad_dot = dot(grad, grad);
    invlen = inversesqrt(grad_dot);
    edgeAlpha *= clamp(0.5 + test * invlen, 0.0, 1.0);
    vec4 outputCoverage_S0 = vec4(edgeAlpha);
    {
        sk_FragColor = outputColor_S0 * outputCoverage_S0;
    }
}
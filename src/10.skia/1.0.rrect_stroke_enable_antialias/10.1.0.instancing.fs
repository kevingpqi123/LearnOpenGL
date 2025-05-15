#version 400

out vec4 sk_FragColor;
noperspective in vec4 vinCircleEdge_S0;
noperspective in vec4 vinColor_S0;
void main() {
    vec4 circleEdge = vinCircleEdge_S0;
    vec4 outputColor_S0 = vinColor_S0;
    float d = length(circleEdge.xy);
    float distanceToOuterEdge = circleEdge.z * (1.0 - d);
    float edgeAlpha = clamp(distanceToOuterEdge, 0.0, 1.0);
    float distanceToInnerEdge = circleEdge.z * (d - circleEdge.w);
    float innerAlpha = clamp(distanceToInnerEdge, 0.0, 1.0);
    edgeAlpha *= innerAlpha;
    vec4 outputCoverage_S0 = vec4(edgeAlpha);
    {
        sk_FragColor = outputColor_S0 * outputCoverage_S0;
    }
}
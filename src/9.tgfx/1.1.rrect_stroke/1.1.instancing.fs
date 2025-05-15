#version 150

precision mediump float;
uniform vec4 Color_P0;

in highp float Coverage_P0;

out vec4 tgfx_FragColor;

void main() {
    vec4 outputColor_P0;
    vec4 outputCoverage_P0;
    { // Processor0 : DefaultGeometryProcessor
        outputCoverage_P0 = vec4(Coverage_P0);
        outputColor_P0 = Color_P0;
    }
    { // Processor1 : EmptyXferProcessor
        tgfx_FragColor = outputColor_P0 * outputCoverage_P0;
    }
}
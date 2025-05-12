#version 400

out vec4 sk_FragColor;
uniform vec4 uColor_S0;
void main() {
    vec4 outputColor_S0 = uColor_S0;
    {
        sk_FragColor = outputColor_S0;
    }
}
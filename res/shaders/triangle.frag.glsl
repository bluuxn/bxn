#version 460 core

in vec4 vColor;
in vec2 vUV;

uniform sampler2D uTex;

void main() {
    gl_FragColor = texture(uTex, vUV);
}

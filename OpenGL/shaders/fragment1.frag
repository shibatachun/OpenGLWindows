#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float time;

void main()
{
    FragColor = mix(texture(Texture1, TexCoord),texture(Texture2,TexCoord),sin(time)/2.0f+0.5f);
}
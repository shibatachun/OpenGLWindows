
#version 330 core
in vec3 transitColor;
out vec4 FragColor;
void main()
{
  FragColor = vec4(transitColor,1.0f);
};
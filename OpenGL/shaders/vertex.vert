#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 transitColor;
uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection * view * model * vec4(aPos,1.0);
   transitColor = vec3((sin(2*time)/ 2.0f + 0.5f)*aColor.r, (sin(2*time + 2.12)/ 2.0f + 0.5f)*aColor.g, (sin(2*time + 4.14)/ 2.0f + 0.5f)*aColor.b);
};
#version 330 core

uniform vec3 objectColor;

out vec3     FragColor;

void main()
{
    FragColor = objectColor;
}
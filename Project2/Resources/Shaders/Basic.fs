#version 450 core

in vec3 fragColor;

out vec4 color;

uniform float currentTime;

void main()
{
	vec3 colorTemp = fragColor * abs(sin(currentTime));
	color = vec4(colorTemp, 1.0f);
}
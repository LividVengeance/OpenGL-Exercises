#version 450 core

in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

uniform float currentTime;
uniform sampler3D tex;

void main()
{
	color = texture(tex, fragTexCoord);
}
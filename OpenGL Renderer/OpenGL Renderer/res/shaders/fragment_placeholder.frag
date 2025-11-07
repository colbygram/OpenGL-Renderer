#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture;

void main()
{
	vec2 flipped = vec2(texCoord.x, 1.0 - texCoord.y);
	FragColor    = texture(texture, flipped) * vertexColor;
}
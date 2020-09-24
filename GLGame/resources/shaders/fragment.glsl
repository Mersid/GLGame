#version 330 core

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texturei;

void main()
{
	FragColor = vec4(vertexColor, 1.0f);
	FragColor = texture(texturei, TexCoord) * vec4(vertexColor, 1.0f);
}

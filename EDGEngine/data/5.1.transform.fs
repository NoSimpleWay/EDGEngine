

#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = (texture(texture1, TexCoord) + texture(texture1, TexCoord + vec2(0.0000820,0)) + texture(texture1, TexCoord + vec2(0,0.0000820)) + texture(texture1, TexCoord + vec2(0.0000820,0.0000820))) / 4 * ourColor;
}




#version 330 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

float move = 0;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor =
	(
		texture(texture1, TexCoord + vec2(move, 1.0/8192.0 + move))
		+
		texture(texture1, TexCoord + vec2(move, 1.0/8192.0 + move))
		+
		texture(texture1, TexCoord + vec2(1.0/8192.0 + move, move))
		+
		texture(texture1, TexCoord + vec2(1.0/8192.0 + move, 1.0/8192.0 + move))
	) / 4.0 * ourColor ;
}


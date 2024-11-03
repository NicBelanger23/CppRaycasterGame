#version 430
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureSampler;


void main()
{
	float y = TexCoord.x;
	float x = TexCoord.y;

	//that last 0.9 fixes white lines on edge of blocks
   	vec2 newv = vec2(x + 0.25, y + 0.25);
	vec4 c = texture(textureSampler, newv * 2);
	if(c.w < 1){discard;}
	FragColor = c;
}
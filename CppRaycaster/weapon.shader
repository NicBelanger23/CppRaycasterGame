#version 430
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureSampler;
uniform int State;

void main()
{
	float s = 1.0 * State * 4.0/3.0; 
	if(TexCoord.x < 0){discard;}

	if(TexCoord.y > 0){discard;}

	float x = 0.05 + ((TexCoord.x / 4) + s);
	float y = (-TexCoord.y * 0.66) - 0.66;

	vec2 pos = vec2(x, y);

	vec4 c = texture(textureSampler, pos);
	if(c.w < 0.5){discard;}
	FragColor = c;
}
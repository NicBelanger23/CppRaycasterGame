#version 430
out vec4 FragColor;
in vec3 ourColor;
	
uniform int Width;
in vec2 TexCoord;

uniform sampler2D textureSampler;

layout(std430, binding = 1) buffer FloatArrayBuffer {
    float data[]; // Unsized array
} floatArray;

uniform int dataSize;

void main()
{
	float x = TexCoord.x;
	float y = TexCoord.y;

	int calcIndex = int((ourColor.x + 1)/2 * Width) * 4;

	float multiplier = floatArray.data[calcIndex] / 4;
	float dist = floatArray.data[calcIndex + 1]; 

	//how far along the block is the collision
	float collOff = floatArray.data[calcIndex + 2] / 2; 


	//which position in texture atlas
	float pos = floatArray.data[calcIndex + 3] / 2; 

	//move to position in textureatlas

	//that last 0.9 fixes white lines on edge of blocks

   	vec2 newv = vec2((collOff) + pos, 0.25-(y/4) * dist * 0.9);
	FragColor = texture(textureSampler, newv) * multiplier;
}
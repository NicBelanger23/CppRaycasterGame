#version 430
out vec4 FragColor;
in vec3 ourColorb;
	
uniform int Width;
in vec2 TexCoordb;

uniform sampler2D MapTextures;

layout(std430, binding = 1) buffer FloatArrayBuffer {
    float data[]; // Unsized array
} floatArray;

uniform float AnglePlayer;
uniform float DistPlayer;

void main()
{
	float y = TexCoordb.x;
	float x = TexCoordb.y;

	int calcIndex = int((gl_FragCoord.x)) * 4;

	//float multiplier = floatArray.data[calcIndex] / 4;
	float dist = floatArray.data[calcIndex + 1]; 


	//that last 0.9 fixes white lines on edge of blocks
   	vec2 newv = vec2(x, y);
	   
	if( dist > DistPlayer){
			FragColor = vec4(1/DistPlayer,0.2,0.2,1);
	}
	else{
		discard;
	}

}
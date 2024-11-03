#version 430
out vec4 FragColor;
in vec3 ourColor;
	
uniform int Width;
in vec2 TexCoord;

uniform sampler2D textureSampler;

layout(std430, binding = 1) buffer FloatArrayBuffer {
    float data[]; // Unsized array
} floatArray;

uniform float AnglePlayer;
uniform float DistPlayer;

void main()
{

	float x = (TexCoord.x + AnglePlayer * 2) * DistPlayer;
	float y = TexCoord.y * DistPlayer;

	int calcIndex = int((gl_FragCoord.x)) * 4;

	//float multiplier = floatArray.data[calcIndex] / 4;
	float dist = floatArray.data[calcIndex + 1]; 


	//that last 0.9 fixes white lines on edge of blocks
   	vec2 newv = vec2(x + 0.5, -y / 1.4 + 0.3);
	   
	if( dist > DistPlayer){
		vec4 c = texture(textureSampler, newv);
		if(c.w < 1){discard;}
		FragColor = c / DistPlayer;
			//FragColor = vec4(1/DistPlayer,0.2,0.2,1);
	}
	else{
		discard;
	}

}
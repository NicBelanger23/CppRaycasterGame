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
uniform float State;
void main()
{
	float angle = AnglePlayer;
	float x = ((TexCoord.x + angle * 2) * DistPlayer)/2 - 0.25f + (State / 2);
	float y = TexCoord.y * DistPlayer;
	
	int calcIndex = int((gl_FragCoord.x)) * 4;

	//float multiplier = floatArray.data[calcIndex] / 4;
	float dist = floatArray.data[calcIndex + 1];
	if (angle < 0) { angle += 2 * 3.14f; }
    if (angle > 2 * 3.14) { angle -= 2 * 3.14f; } 
	dist /= cos(angle);

	//that last 0.9 fixes white lines on edge of blocks
   	vec2 newv = vec2(x + 0.5, -y / 1.4 + 0.25);
	 
	if( dist > DistPlayer){
		vec4 c = texture(textureSampler, newv);

		if(c.w < 1){discard;}
		if(DistPlayer < 2){FragColor = c;}
		else{FragColor = c / (DistPlayer * 0.5);}

	}
	else{
		discard;
	}

}
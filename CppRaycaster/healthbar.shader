#version 430
out vec4 FragColor;

in vec2 TexCoord;
uniform float Health;
uniform float Ammo;

void main()
{
	if(TexCoord.x > -0.9){discard;}
	if(TexCoord.x < -0.95){
		if(TexCoord.y > (Health * 1.2) - 1){
			FragColor = vec4(0, 0, 0, 1);
		}
		else{
			FragColor = vec4(1-(1 * Health), 1 * Health, 0, 1);
		}
	}
	else{
		if(TexCoord.y > (Ammo * 1.2) - 1){
			FragColor = vec4(0, 0, 0, 1);
		}
		else{
			FragColor = vec4(0.2, 0.8, 0.8, 1);
		}
	
	}


}
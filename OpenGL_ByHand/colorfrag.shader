#version 410 core
out vec4 FragColor;
//we output a vector with 4 parameters (RGB+A)

//expect input of 3 vectors for RGB
in vec3 vertexColor;


//uniform vec4 vertexColor;
uniform sampler2D ourTexture;

void main()
{

	FragColor = vec4(vertexColor, 1.0);
	//FragColor = texture(ourTexture, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);
}
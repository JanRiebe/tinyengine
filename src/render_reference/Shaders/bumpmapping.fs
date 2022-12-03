#version 420 core
precision highp float;

uniform sampler2D TexDiffuse;
uniform sampler2D TexNormal;
uniform vec3 LightDirection;
uniform vec3 LightColor;

in VertexData
{
	vec3 Tangent1;
	vec3 Tangent2;
	vec3 Normal;
	vec2 TexCoords;
} inData;

out vec4 outColor;
void main(void)
{
	vec3 normalMapTexel = vec3(texture(TexNormal, inData.TexCoords));
	vec3 normal;
	normal.x = normalMapTexel.x - 0.5;
	normal.y = normalMapTexel.y - 0.5;
	normal.z = normalMapTexel.z - 0.5;
	
	normal = normalize(normal);
	
	normal = inData.Tangent1 * normal.x + 
			inData.Tangent2 * normal.y + 
			inData.Normal * normal.z;

	outColor = texture(TexDiffuse, inData.TexCoords) * abs(dot(normal, LightDirection));
	
	// Do nothing but prevent all variables from being optimized out.
	if(outColor.x > 0 && outColor.x < 0)
	{
		outColor = texture(TexDiffuse, inData.TexCoords) * 
				texture(TexNormal, inData.TexCoords);
	}
}


/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;
smooth out vec4 boneColor;

out vec4 outboneIndices;
out vec3 viewVector;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	boneColor = boneWeights;
	outboneIndices = boneIndices;
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = vec4(inputPosition, 1.0f);
	//vec4 pos = vec4(0.0f,0.0f,0.0f,1.0f);

	vec4 finalpos = (pos * skin.mat[int(boneIndices.x)]) * boneWeights.x +
					(pos * skin.mat[int(boneIndices.y)]) * boneWeights.y +
					(pos * skin.mat[int(boneIndices.z)]) * boneWeights.z +
					(pos * skin.mat[int(boneIndices.w)]) * boneWeights.w;

	mat4 MVP 		= sm.projectionMatrix * modelViewMatrix;
	//gl_Position		= sm.projectionMatrix * (modelViewMatrix * vec4(finalpos.xyz, 1.0f));
	gl_Position		= MVP * vec4(finalpos.xyz, 1.0f);

	//gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(pos.xyz, 1.0f));
	//outNormal = mat3(modelViewMatrix) * normal;
	
	outNormal = (normal * mat3(skin.mat[int(boneIndices.x)])) * boneWeights.x +
	 			(normal * mat3(skin.mat[int(boneIndices.y)])) * boneWeights.y +
				(normal * mat3(skin.mat[int(boneIndices.z)])) * boneWeights.z;

	outNormal = mat3(modelViewMatrix) * outNormal; 

	outNormal = normalize(outNormal);
	
	mat3 rotMat = mat3(modelViewMatrix);
	vec3 d =  modelViewMatrix[3].xyz;

	vec3 CameraPos = -d * rotMat;

	viewVector = CameraPos - (modelViewMatrix * vec4(pos.xyz, 1.0f)).xyz;
}

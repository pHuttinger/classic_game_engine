//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "SkinnedMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
	PS_INPUT output;

	float4 pos = float4(input.position, 1.0f);

	float4x4 skin =
	data.m_bones[input.boneIndices.x] * input.boneWeights.x +
	data.m_bones[input.boneIndices.y] * input.boneWeights.y +
	data.m_bones[input.boneIndices.z] * input.boneWeights.z +
	data.m_bones[input.boneIndices.w] * input.boneWeights.w;

	float4 skinnedPos = mul(skin, pos);

	output.position = mul(skinnedPos, data.m_mvp);
	output.normal   = mul(input.normal, (float3x4) mul(skin, data.m_model));
	output.texcoord = input.texcoord;
	
	return output;
}
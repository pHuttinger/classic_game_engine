//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "SkinnedMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
  PS_INPUT output;

  output.position = mul(float4(input.position, 1.0f), data.m_mvp);
  output.normal   = mul(input.normal, (float3x4) data.m_model);
  output.texcoord = input.texcoord;
  output.model    = mul(float4(input.position, 1.0f), data.m_model);
	
  return output;
}

/*
#define MAX_BONES 128

cbuffer TransformBuffer : register(b0)
{
    float4x4 WorldViewProjection;
};

cbuffer BoneBuffer : register(b1)
{
    float4x4 Bones[MAX_BONES];
};

struct VS_INPUT
{
    float3 Position  : POSITION;
    float3 Normal    : NORMAL;
    uint4  BoneIndex : BLENDINDICES;
    float4 BoneWeight : BLENDWEIGHT;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float3 Normal   : NORMAL;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;

    float4 pos = float4(input.Position, 1.0f);

    // Skinning-Matrix aus vier Bone-Influences
    float4x4 skin =
        Bones[input.BoneIndex.x] * input.BoneWeight.x +
        Bones[input.BoneIndex.y] * input.BoneWeight.y +
        Bones[input.BoneIndex.z] * input.BoneWeight.z +
        Bones[input.BoneIndex.w] * input.BoneWeight.w;

    // Vertex durch das Skelett transformieren
    float4 skinnedPos = mul(skin, pos);

    // In Clip Space transformieren
    output.Position = mul(WorldViewProjection, skinnedPos);

    // Vereinfachte Normalentransformation
    output.Normal = normalize(
        mul((float3x3)skin, input.Normal)
    );

    return output;
}
*/
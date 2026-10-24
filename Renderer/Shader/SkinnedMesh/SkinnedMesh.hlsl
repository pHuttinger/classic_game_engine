//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "SkinnedMeshSharedResources.h"

cbuffer VS_CBUFFER
{
	TSkinnedMeshVertexShaderData data;
};

struct VS_INPUT
{
  float3 position    : POSITION;
  float3 normal      : NORMAL;
  float2 texcoord    : TEXCOORD;
	uint4  boneIndices : BLENDINDICES;
	float4 boneWeights : BLENDWEIGHT;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  float3 normal   : NORMAL;
  float2 texcoord : TEXCOORD;
};

struct PS_OUTPUT
{
  float4 albedo   : SV_Target0;
  float4 normal   : SV_Target1;
};
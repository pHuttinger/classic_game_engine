//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMeshSharedResources.h"

cbuffer VS_CBUFFER
{
	TStaticMeshVertexShaderData data;
};

struct VS_INPUT
{
  float3 position : POSITION;
  float3 normal   : NORMAL;
  float2 texcoord : TEXCOORD;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  float3 model    : POSITION1;
  float3 normal   : NORMAL;
  float2 texcoord : TEXCOORD;
};

struct PS_OUTPUT
{
  float4 albedo : SV_Target0;
  float4 normal : SV_Target1;
};
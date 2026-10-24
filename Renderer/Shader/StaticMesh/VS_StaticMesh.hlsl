//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
  PS_INPUT output;

  output.position = mul(float4(input.position, 1.0f), data.m_mvp);
  output.normal   = mul(input.normal, (float3x4) data.m_model);
  output.texcoord = input.texcoord;
	
  return output;
}
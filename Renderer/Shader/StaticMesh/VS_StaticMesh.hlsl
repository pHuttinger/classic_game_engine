//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
  PS_INPUT output;

  output.position = mul(float4(input.position, 1.0f), mvp);
  output.normal   = mul(input.normal, (float3x4) model);
  output.texcoord = input.texcoord;
  output.model    = mul(float4(input.position, 1.0f), model);
	
  return output;
}
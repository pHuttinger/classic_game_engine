//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

PS_INPUT VSMain(VS_INPUT input)
{
  PS_INPUT output;

  output.position = mul(input.position, mvp);
  output.normal   = mul(input.normal, (float3x4) model);
  output.texcoord = input.texcoord;
  output.model    = mul(input.position, model);
	
  return output;
}
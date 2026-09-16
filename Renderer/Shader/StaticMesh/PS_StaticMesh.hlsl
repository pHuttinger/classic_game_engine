//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  float4 diffuse = texture1.Sample(samplerState1, input.TexCoord);
  
  clip(1.0 - all(diffuse.rgb == 1.0));

  return diffuse;
}
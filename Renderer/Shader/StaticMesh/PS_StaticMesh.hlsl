//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

SamplerState samplerState : register(s0);

Texture2D texture1 : register(t0);

PS_OUTPUT PSMain(PS_INPUT input)
{
  PS_OUTPUT output;
  
  output.albedo = texture1.Sample(samplerState, input.texcoord);
  clip(1.0 - all(output.albedo.rgb == 1.0));
  
  output.normal = float4(normalize(input.normal), 1.0);

  return output;
}

//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "StaticMesh.hlsl"

PS_OUTPUT PSMain(PS_INPUT input) : SV_TARGET
{
  PS_OUTPUT output;
  
  output.albedo = texture1.Sample(samplerState1, input.texcoord);
  clip(1.0 - all(output.albedo.rgb == 1.0));
  
  output.normal = float4(normalize(input.normal), 1.0);

  return output;
}

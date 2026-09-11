//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "RenderTarget.hlsl"

Texture2D textureAlbedo : register(t0);
//Texture2D textureNormals : register(t1);
SamplerState objSampler : register(s0);

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  float3 albedo = textureAlbedo.Sample(objSampler, input.texcoord).rgb;
  //float3 normal = textureNormals.Sample(objSampler, input.Texcoord).xyz;
  
  float3 finalColor = albedo;

  return float4(finalColor, 1.0f);
}
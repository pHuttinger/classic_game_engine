//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "RenderTarget.hlsl"

SamplerState samplerState : register(s0);

Texture2D textureAlbedo : register(t0);
Texture2D textureNormal : register(t1);

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  float4 albedo = textureAlbedo.Sample(samplerState, input.texcoord);
  float4 normal = textureNormal.Sample(samplerState, input.texcoord);
  
  float NdotL = saturate(dot(float3(0.3f, 0.5f, 0.7f), float3(normal.x, normal.y, normal.z)));

  return albedo * NdotL;
}
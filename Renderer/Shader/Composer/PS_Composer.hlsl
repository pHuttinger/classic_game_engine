//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "Composer.hlsl"

SamplerState samplerState : register(s0);

Texture2D textureAlbedo : register(t0);
Texture2D textureNormal : register(t1);

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  float4 albedo = textureAlbedo.Sample(samplerState, input.texcoord);
  float4 normal = textureNormal.Sample(samplerState, input.texcoord);
  
  clip(albedo.a == 0.0f ? -1 : 1);
  
	float NdotL = saturate(dot(normalize(data.m_lightDirection), float3(normal.x, normal.y, normal.z)));

  float3 finalColor = albedo.rgb * (NdotL + 0.1f);
  
  return float4(finalColor, albedo.a);
}
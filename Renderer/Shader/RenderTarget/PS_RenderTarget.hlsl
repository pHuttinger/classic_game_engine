//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "RenderTarget.hlsl"

Texture2D textureAlbedo : register(t0);
//Texture2D textureNormals : register(t1);
SamplerState samplerState : register(s0);

float4 PSMain(PS_INPUT input) : SV_TARGET
{
  float4 albedo = textureAlbedo.Sample(samplerState, input.texcoord);
  //float4 normal = textureNormals.Sample(objSampler, input.Texcoord);

  return albedo;
}
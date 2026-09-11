//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

struct VS_INPUT
{
  float4 position : POSITION;
  float2 texcoord : TEXCOORD;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  float2 texcoord : TEXCOORD0;
};
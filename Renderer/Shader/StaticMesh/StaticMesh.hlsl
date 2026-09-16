//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

//struct Light
//{
//  float3 dir;
//  float4 ambient;
//  float4 diffuse;
//};

//cbuffer cbPerFrame
//{
//  Light light;
//  float engineTime;
//  float3 cameraPos;
//};

cbuffer cbPerObject
{
  float4x4 MVP;
  float4x4 World;
};

Texture2D texture1;
SamplerState samplerState1;

struct VS_INPUT
{
  float4 inPos : POSITION;
  float2 inTexCoord : TEXCOORD;
  float3 normal : NORMAL;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float3 WorldPos : POSITION1;
  float2 TexCoord : TEXCOORD;
  float3 normal : NORMAL;
};
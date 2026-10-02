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
  float4x4 mvp;
  float4x4 model;
};

Texture2D texture1;
SamplerState samplerState1;

struct VS_INPUT
{
  float3 position : POSITION;
  float3 normal   : NORMAL;
  float2 texcoord : TEXCOORD;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  float3 model    : POSITION1;
  float3 normal   : NORMAL;
  float2 texcoord : TEXCOORD;
};
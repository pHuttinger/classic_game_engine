/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common/BeginSharedResources.h"

//----------------------------------------------------
// TComposerPixelShaderData
//----------------------------------------------------
struct TComposerPixelShaderData __FINAL__
{
  float3 m_lightDirection;
  float _padding0;
  float3 m_cameraPosition;
  float _padding1;
  float3 m_fogColor;
  float _padding2;
};

#include "../Common/EndSharedResources.h"

/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common/BeginSharedResources.h"

//----------------------------------------------------
// TComposerPixelShaderData
//----------------------------------------------------
struct TComposerPixelShaderData FINAL
{
  float3 m_lightDirection;
  PADDING(0)
  float3 m_cameraPosition;
  PADDING(1)
};

#include "../Common/EndSharedResources.h"

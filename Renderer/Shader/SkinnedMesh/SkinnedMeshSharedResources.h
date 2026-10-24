/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common/BeginSharedResources.h"

#define CGE_MAX_BONES 96U

//----------------------------------------------------
// TSkinnedMeshVertexShaderData
//----------------------------------------------------
struct TSkinnedMeshVertexShaderData FINAL
{
  float4x4 m_mvp;
  float4x4 m_model;
  float4x4 m_bones[CGE_MAX_BONES];
};

#include "../Common/EndSharedResources.h"

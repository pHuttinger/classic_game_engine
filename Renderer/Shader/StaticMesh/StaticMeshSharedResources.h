/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common/BeginSharedResources.h"

//----------------------------------------------------
// TStaticMeshVertexShaderData
//----------------------------------------------------
struct TStaticMeshVertexShaderData FINAL
{
  float4x4 m_mvp;
  float4x4 m_model;
};

#include "../Common/EndSharedResources.h"

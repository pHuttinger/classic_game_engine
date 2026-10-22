//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Common.h"

namespace cge
{
//----------------------------------------------------
// TStaticMeshModel
//----------------------------------------------------
struct TStaticMeshModel final
{
  std::vector<TVertexStaticMesh> m_vertices;
  std::vector<uint32_t>          m_indices;
  std::vector<std::string>       m_textureNames;
};

//----------------------------------------------------
// TActorModel
//----------------------------------------------------
struct TActorModel final
{
  std::vector<TStaticMeshModel> m_staticMeshModels;
};
}

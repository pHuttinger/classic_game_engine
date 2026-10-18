//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::render
{
//----------------------------------------------------
// ERasterizerState
//----------------------------------------------------
enum class ERasterizerState
{
  Solid,
  SolidNoCull,
  Wireframe,
};

//----------------------------------------------------
// TVertexStaticMesh
//----------------------------------------------------
struct TVertexStaticMesh final
{
  glm::vec3 m_position;
  glm::vec3 m_normal;
  glm::vec2 m_texcoord;
};
}
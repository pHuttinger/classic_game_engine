//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

namespace cge::render
{
//----------------------------------------------------
// EVertexType
//----------------------------------------------------
enum class EVertexType
{
  Undefined,
  StaticMesh,
};

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
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

//----------------------------------------------------
// GLM
//----------------------------------------------------
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace cge
{
//----------------------------------------------------
// EBackend
//----------------------------------------------------
enum class EBackend
{
  Undefined,
  DX11,
  OpenGL,
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

//---------------------------------------------------
// EVertexAttributeUsage
//---------------------------------------------------
enum class EVertexAttributeUsage
{
  Position,
  Texcoord,
  Normal,
};

//---------------------------------------------------
// EVertexAttributeFormat
//---------------------------------------------------
enum class EVertexAttributeFormat
{
  Float2,
  Float3,
};

//---------------------------------------------------
// TVertexAttribute
//---------------------------------------------------
struct TVertexAttribute final
{
  EVertexAttributeUsage  m_usage  = EVertexAttributeUsage::Position;
  EVertexAttributeFormat m_format = EVertexAttributeFormat::Float2;
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
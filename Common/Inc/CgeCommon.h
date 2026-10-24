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
  BlendIndices,
  BlendWeights,
};

//---------------------------------------------------
// EVertexAttributeFormat
//---------------------------------------------------
enum class EVertexAttributeFormat
{
  UInt4 ,
  Float2,
  Float3,
  Float4,
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
  glm::vec3 m_position = glm::vec3(0.0f);
  glm::vec3 m_normal   = glm::vec3(0.0f);
  glm::vec2 m_texcoord = glm::vec2(0.0f);
};

//----------------------------------------------------
// TVertexSkinnedMesh
//----------------------------------------------------
struct TVertexSkinnedMesh final
{
  glm::vec3  m_position    = glm::vec3(0.0f);
  glm::vec3  m_normal      = glm::vec3(0.0f);
  glm::vec2  m_texcoord    = glm::vec2(0.0f);
  glm::uvec4 m_boneIndices = glm::uvec4(0);
  glm::vec4  m_boneWeights = glm::vec4(0.0f);
};
}
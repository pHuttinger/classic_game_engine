//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Common.h"

namespace cge
{
//----------------------------------------------------
// EMeshType
//----------------------------------------------------
enum EMeshType
{
  Static,
  Skinned
};

//----------------------------------------------------
// TVertexModel
//----------------------------------------------------
struct TVertexModel final
{
  glm::vec3  m_position    = glm::vec3(0.0f);
  glm::vec3  m_normal      = glm::vec3(0.0f);
  glm::vec2  m_texcoord    = glm::vec2(0.0f);
  glm::uvec4 m_boneIndices = glm::uvec4(0);
  glm::vec4  m_boneWeights = glm::vec4(0.0f);
};

//----------------------------------------------------
// TMeshModel
//----------------------------------------------------
struct TMeshModel final
{
  EMeshType                 m_meshType = EMeshType::Static;
  std::vector<TVertexModel> m_vertices;
  std::vector<uint32_t>     m_indices;
  std::vector<std::string>  m_textureNames;
};

//----------------------------------------------------
// TActorModel
//----------------------------------------------------
struct TActorModel final
{
  std::vector<TMeshModel> m_meshModels;
};
}

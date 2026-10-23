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
  glm::vec3  m_position;
  glm::vec3  m_normal;
  glm::vec2  m_texcoord;
  glm::ivec4 m_boneIDs;
  glm::vec4  m_boneWeights;
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

//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Common.h"

namespace cge
{
constexpr const size_t CGE_NUM_BONE_WEIGHTS = 4U;

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
// TWeight
//----------------------------------------------------
struct TWeight final
{
  size_t m_boneIndex = 0U;
  float  m_weight = 0.0f;
};

//----------------------------------------------------
// TSkeletonSnapshot
//----------------------------------------------------
struct TSkeletonSnapshot final
{
  std::vector<glm::mat4> m_boneTransforms;
  float                  m_timeOfSnapshot = 0.0f;
};

//----------------------------------------------------
// TAnimation
//----------------------------------------------------
struct TAnimation final
{
  std::vector<TSkeletonSnapshot> m_keyFrame;
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
  std::vector<glm::mat4>    m_boneTransforms;
  std::vector<TAnimation>   m_animations;
};

//----------------------------------------------------
// TActorModel
//----------------------------------------------------
struct TActorModel final
{
  std::vector<TMeshModel> m_meshModels;
};
}

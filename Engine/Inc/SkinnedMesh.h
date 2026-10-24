//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>
#include <Common/Inc/ImportModel.h>
#include "Camera.h"
#include "Transform.h"
#include <Renderer/Shader/SkinnedMesh/SkinnedMeshSharedResources.h>

namespace cge
{
//----------------------------------------------------
// TSkinnedMeshCreateInfo
//----------------------------------------------------
struct TSkinnedMeshCreateInfo final
{
  std::vector<TVertexSkinnedMesh> m_vertices;
  std::vector<uint32_t>           m_indices;
  std::vector<std::string>        m_textureNames;
  std::vector<glm::mat4>          m_boneTransforms;
  std::vector<TAnimation>         m_animations;
};

//----------------------------------------------------
// CSkinnedMesh
//----------------------------------------------------
class CSkinnedMesh
{
friend class CActor;
friend class CSceneManager;
friend class CAssetManager;

public:

  TResult Initialize(render::CRenderer& renderer, const render::TDrawItemCreateInfo& createInfo);
  TResult SetRasterizerState(const ERasterizerState state);

private:

  void UpdateVertexShaderData(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix);
  TResult GetVertexShaderData(render::CRenderer& renderer, std::shared_ptr<render::CShaderData>& pShaderData);
  void SetBoneTransforms(const std::vector<glm::mat4>& transforms);

  static std::vector<TVertexAttribute> GetVertexAttributes();
  static std::string GetVertexShaderName() { return "VS_SkinnedMesh"; };
  static std::string GetPixelShaderName() { return "PS_SkinnedMesh"; };

  render::CDrawItem* GetDrawItem() const { return m_pDrawItem.get(); };

  std::unique_ptr<render::CDrawItem> m_pDrawItem;
  TSkinnedMeshVertexShaderData       m_vertexShaderData;
  std::vector<TAnimation>            m_animations;
};
}
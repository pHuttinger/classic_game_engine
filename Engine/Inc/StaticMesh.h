//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>
#include "Camera.h"
#include "Transform.h"
#include <Renderer/Shader/StaticMesh/StaticMeshSharedResources.h>

namespace cge
{
//----------------------------------------------------
// TStaticMeshCreateInfo
//----------------------------------------------------
struct TStaticMeshCreateInfo final
{
  std::vector<TVertexStaticMesh> m_vertices;
  std::vector<uint32_t>          m_indices;
  std::vector<std::string>       m_textureNames;
};

//----------------------------------------------------
// CStaticMesh
//----------------------------------------------------
class CStaticMesh
{
friend class CActor;
friend class CSceneManager;

public:

  TResult Initialize(render::CRenderer& renderer, const render::TDrawItemCreateInfo& createInfo);
  TResult SetRasterizerState(const ERasterizerState state);

private:

  void UpdateVertexShaderData(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix);
  TResult GetVertexShaderData(render::CRenderer& renderer, std::shared_ptr<render::CShaderData>& pShaderData);

  render::CDrawItem* GetDrawItem() const { return m_pDrawItem.get(); };

  std::unique_ptr<render::CDrawItem> m_pDrawItem;
};
}
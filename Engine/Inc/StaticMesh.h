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
  TDataHandle              m_vertexData;
  TDataHandle              m_indexData;
  size_t                   m_indexCount = 0U;
  std::vector<std::string> m_textureNames;
};

//----------------------------------------------------
// CStaticMesh
//----------------------------------------------------
class CStaticMesh
{
public:

  TResult Initialize(render::CRenderer& renderer, const render::TDrawItemCreateInfo& createInfo);
  TResult GetVertexShaderData(render::CRenderer& renderer, std::shared_ptr<render::CShaderData>& pShaderData);

  void Update(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix);

  TResult SetRasterizerState(const ERasterizerState state);

  render::CDrawItem* GetDrawItem() const { return m_pDrawItem.get(); };

private:

  std::unique_ptr<render::CDrawItem> m_pDrawItem;
};
}
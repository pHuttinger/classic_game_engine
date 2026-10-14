//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/StaticMesh.h"

namespace cge
{
TResult CStaticMesh::Initialize(render::CRenderer& renderer, const render::TDrawItemCreateInfo& createInfo)
{
  CGE_TRY(renderer.GetDrawItemFactory().CreateDrawItem(createInfo, m_pDrawItem));
  return TResult::Okay();
}

void CStaticMesh::Update(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix)
{
  glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
  glm::mat4 viewMatrix       = camera.GetViewMatrix();

  TStaticMeshShaderData dataObj{};
  dataObj.m_mvp   = glm::transpose(projectionMatrix * viewMatrix * modelMatrix);
  dataObj.m_model = glm::transpose(modelMatrix);

  TDataHandle dataHandle
  {
    .m_size  = sizeof(TStaticMeshShaderData),
    .m_pData = &dataObj,
  };

  pShaderData->SetData(dataHandle);
}

TResult CStaticMesh::SetRasterizerState(const render::ERasterizerState state)
{
  return m_pDrawItem->SetRasterizerState(state);
}
}

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

TResult CStaticMesh::GetVertexShaderData(render::CRenderer& renderer, std::shared_ptr<render::CShaderData>& pShaderData)
{
  pShaderData = std::make_shared<render::CShaderData>(renderer);

  render::TShaderDataCreateInfo shaderDataCreateInfo
  {
    .m_size        = sizeof(TStaticMeshVertexShaderData),
    .m_destination = render::EShaderDataDestination::Vertex,
  };

  CGE_TRY(pShaderData->Initialize(shaderDataCreateInfo));

  return TResult::Okay();
}

void CStaticMesh::Update(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix)
{
  glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
  glm::mat4 viewMatrix       = camera.GetViewMatrix();

  TStaticMeshVertexShaderData vertexShaderData{};
  vertexShaderData.m_mvp   = glm::transpose(projectionMatrix * viewMatrix * modelMatrix);
  vertexShaderData.m_model = glm::transpose(modelMatrix);

  TDataHandle dataHandle
  {
    .m_size  = sizeof(TStaticMeshVertexShaderData),
    .m_pData = &vertexShaderData,
  };

  pShaderData->SetData(dataHandle);
}

TResult CStaticMesh::SetRasterizerState(const ERasterizerState state)
{
  return m_pDrawItem->SetRasterizerState(state);
}
}

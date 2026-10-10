//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/StaticMesh.h"

namespace cge
{
TResult CStaticMesh::Initialize(render::CRenderer& renderer, const render::TMeshCreateInfo& createInfo)
{
  CGE_TRY(renderer.GetMeshFactory().CreateMesh(createInfo, m_pMeshData));

  render::TShaderDataCreateInfo shaderDataCreateInfo
  {
    .m_size = sizeof(TStaticMeshShaderData)
  };

  m_pShaderData = std::make_unique<render::CShaderData>(renderer);
  CGE_TRY(m_pShaderData->Initialize(shaderDataCreateInfo));

  return TResult::Okay();
}

void CStaticMesh::Update(const CCamera& camera, CTransform& transform)
{
  glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
  glm::mat4 viewMatrix       = camera.GetViewMatrix();
  glm::mat4 modelMatrix      = transform.GetModelMatrix();

  TStaticMeshShaderData cbData{};
  cbData.m_mvp   = glm::transpose(projectionMatrix * viewMatrix * modelMatrix);
  cbData.m_model = glm::transpose(modelMatrix);

  TDataHandle dataHandle
  {
    .m_size  = sizeof(TStaticMeshShaderData),
    .m_pData = &cbData,
  };

  m_pShaderData->SetData(dataHandle);
}
}

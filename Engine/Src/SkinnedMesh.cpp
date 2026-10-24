//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/SkinnedMesh.h"

namespace cge
{
TResult CSkinnedMesh::Initialize(render::CRenderer& renderer, const render::TDrawItemCreateInfo& createInfo)
{
  CGE_TRY(renderer.GetDrawItemFactory().CreateDrawItem(createInfo, m_pDrawItem));
  return TResult::Okay();
}

TResult CSkinnedMesh::GetVertexShaderData(render::CRenderer& renderer, std::shared_ptr<render::CShaderData>& pShaderData)
{
  pShaderData = std::make_shared<render::CShaderData>(renderer);

  render::TShaderDataCreateInfo shaderDataCreateInfo
  {
    .m_size        = sizeof(TSkinnedMeshVertexShaderData),
    .m_destination = render::EShaderDataDestination::Vertex,
  };

  CGE_TRY(pShaderData->Initialize(shaderDataCreateInfo));

  return TResult::Okay();
}

//static
std::vector<TVertexAttribute> CSkinnedMesh::GetVertexAttributes()
{
  return
  {
     {EVertexAttributeUsage::Position    , EVertexAttributeFormat::Float3},
     {EVertexAttributeUsage::Normal      , EVertexAttributeFormat::Float3},
     {EVertexAttributeUsage::Texcoord    , EVertexAttributeFormat::Float2},
     {EVertexAttributeUsage::BlendIndices, EVertexAttributeFormat::UInt4 },
     {EVertexAttributeUsage::BlendWeights, EVertexAttributeFormat::Float4},
  };
}

void CSkinnedMesh::UpdateVertexShaderData(render::CShaderData* pShaderData, const CCamera& camera, const glm::mat4& modelMatrix)
{
  glm::mat4 projectionMatrix = camera.GetProjectionMatrix();
  glm::mat4 viewMatrix       = camera.GetViewMatrix();

  TSkinnedMeshVertexShaderData vertexShaderData{};
  vertexShaderData.m_mvp   = glm::transpose(projectionMatrix * viewMatrix * modelMatrix);
  vertexShaderData.m_model = glm::transpose(modelMatrix);

  TDataHandle dataHandle
  {
    .m_size  = sizeof(TSkinnedMeshVertexShaderData),
    .m_pData = &vertexShaderData,
  };

  pShaderData->SetData(dataHandle);
}

TResult CSkinnedMesh::SetRasterizerState(const ERasterizerState state)
{
  return m_pDrawItem->SetRasterizerState(state);
}
}

/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/App/RenderProxy.h"

namespace cge
{
CRenderProxy::CRenderProxy()
{
}

TResult CRenderProxy::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_renderer.Initialize(createInfo));

  //TODO remove
  render::TMeshCreateInfo mci;
  mci.m_pixelShaderName  = "PS_RenderTarget";
  mci.m_vertexShaderName = "VS_RenderTarget";
  mci.m_vertexType       = render::EVertexType::PositionNormalTexcoord;
  mci.m_indexCount       = 6U;
  mci.m_textureName      = "image.png";
  CGE_TRY(CreateStaticMesh(mci, m_pStaticMesh));
  //TODO remove

  return TResult::Okay();
}

TResult CRenderProxy::CreateStaticMesh(const render::TMeshCreateInfo& createInfo, std::unique_ptr<CStaticMesh>& pStaticMesh)
{
  pStaticMesh = std::make_unique<CStaticMesh>();
  CGE_TRY(pStaticMesh->Initialize(m_renderer, createInfo));
  return TResult::Okay();
}

void CRenderProxy::RenderFrame()
{
  //TODO remove
  m_frameInput.AddDrawCall({ m_pStaticMesh->GetMeshData(), { m_pStaticMesh->GetShaderData() } });
  //TODO remove
  m_renderer.RenderFrame(m_frameInput);
  m_frameInput.Reset();
}
}
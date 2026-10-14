//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/GeometryPass.h"

namespace cge::render
{
constexpr glm::vec4 CLEAR_COLOR_TRANSPARENT = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

CGeometryPass::CGeometryPass(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CGeometryPass::Initialize()
{
  CGE_TRY(CreateDepthBuffer());
  CGE_TRY(m_renderer.GetResourceManager().GetSampler(m_pSampler));

  CGE_TRY(CreateRenderTarget(m_pRenderTarget_Albedo));
  CGE_TRY(CreateRenderTarget(m_pRenderTarget_Normal));

  return TResult::Okay();
}

std::vector<rhi::IRenderTarget*> CGeometryPass::Execute(const CFrameInput& input)
{
  m_pRenderTarget_Albedo->Clear(CLEAR_COLOR_TRANSPARENT);
  m_pRenderTarget_Normal->Clear(CLEAR_COLOR_TRANSPARENT);
  m_pDepthBuffer->Clear();
  m_renderer.GetBackend().GetPipeline().BindRenderTargets(m_renderTargets, m_pDepthBuffer.get());
  m_renderer.GetBackend().GetPipeline().BindSampler(m_pSampler.get());

  for (auto& drawCall : input.GetDrawCalls())
  {
    DrawMesh(*drawCall.m_pDrawItem, drawCall.m_shaderData);
  }

  return m_renderTargets;
}

TResult CGeometryPass::CreateRenderTarget(std::unique_ptr<rhi::IRenderTarget>& renderTarget)
{
  CBackend& backend = m_renderer.GetBackend();
  rhi::TSurfaceCreateInfo surfaceCreateInfo = backend.GetSurface().GetCreateInfo();
  rhi::TRenderTargetCreateInfo createInfo
  {
    .m_width  = surfaceCreateInfo.m_width,
    .m_height = surfaceCreateInfo.m_height  
  };

  CGE_TRY(backend.GetInstance().CreateRenderTarget(createInfo, renderTarget));
  m_renderTargets.push_back(renderTarget.get());
  return TResult::Okay();
}

TResult CGeometryPass::CreateDepthBuffer()
{
  CBackend& backend = m_renderer.GetBackend();
  rhi::TSurfaceCreateInfo surfaceCreateInfo = backend.GetSurface().GetCreateInfo();
  rhi::TDepthBufferCreateInfo createInfo
  {
    .m_width  = surfaceCreateInfo.m_width,
    .m_height = surfaceCreateInfo.m_height
  };

  return backend.GetInstance().CreateDepthBuffer(createInfo, m_pDepthBuffer);
}

void CGeometryPass::DrawMesh(CDrawItem& drawItem, const std::vector<CShaderData*> shaderData)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();

  BindShaderData(shaderData);

  pipeline.BindVertexDescriptor(drawItem.GetSharedMeshResources().m_pVertexDescriptor.get());
  pipeline.BindVertexBuffer    (drawItem.GetGeometryBuffer().m_pVertexBuffer.get());
  pipeline.BindIndexBuffer     (drawItem.GetGeometryBuffer().m_pIndexBuffer.get());
  pipeline.BindVertexShader    (drawItem.GetSharedMeshResources().m_pVertexShader.get());
  pipeline.BindPixelShader     (drawItem.GetSharedMeshResources().m_pPixelShader.get());
  pipeline.BindTextures        (drawItem.GetTextures());
  pipeline.BindRasterizerState (drawItem.GetSharedMeshResources().m_pRasterizerState.get());

  pipeline.DrawIndexed(drawItem.GetCreateInfo().m_indexCount);
}

void CGeometryPass::BindShaderData(const std::vector<CShaderData*>& shaderData)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();

  size_t vertexShaderIndex = 0U, pixelShaderIndex = 0U;
  for (auto* data : shaderData)
  {
    data->UpdateBuffer();

    if (data->GetCreateInfo().m_destination == EShaderDataDestination::Vertex)
    {
      pipeline.BindVertexShaderResources(vertexShaderIndex, data->GetBuffer());
      vertexShaderIndex++;
    }
    else if (data->GetCreateInfo().m_destination == EShaderDataDestination::Pixel)
    {
      pipeline.BindPixelShaderResources(pixelShaderIndex, data->GetBuffer());
      pixelShaderIndex++;
    }
  }
}
}
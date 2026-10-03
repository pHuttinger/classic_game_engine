//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/GeometryPass.h"

namespace cge::render
{
CGeometryPass::CGeometryPass(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CGeometryPass::Initialize()
{
  CGE_TRY(CreateRenderTarget(m_pRenderTarget_Albedo));
  CGE_TRY(CreateDepthBuffer());
  CGE_TRY(m_renderer.GetResourceManager().GetSampler(m_pSampler));

  m_renderTargets.push_back(m_pRenderTarget_Albedo.get());

  return TResult::Okay();
}

std::vector<rhi::IRenderTarget*> CGeometryPass::Execute(const CFrameInput& input)
{
  m_pRenderTarget_Albedo->Clear(input.GetClearColor());
  m_pDepthBuffer->Clear();
  m_renderer.GetBackend().GetPipeline().BindRenderTargets(m_renderTargets, m_pDepthBuffer.get());
  m_renderer.GetBackend().GetPipeline().BindSampler(m_pSampler.get());

  for (auto& drawCall : input.GetDrawCalls())
  {
    RenderMesh(*drawCall.m_pMeshData, drawCall.m_shaderData);
  }

  return
  {
    { m_pRenderTarget_Albedo.get() }
  };
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

  return backend.GetInstance().CreateRenderTarget(createInfo, renderTarget);
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

void CGeometryPass::RenderMesh(CMeshData& meshData, const std::vector<CShaderData*> shaderData)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();

  BindShaderData(shaderData);

  pipeline.BindVertexDescriptor(meshData.GetSharedMeshResources().m_pVertexDescriptor.get());
  pipeline.BindVertexBuffer    (meshData.GetGeometryBuffer().m_pVertexBuffer.get());
  pipeline.BindIndexBuffer     (meshData.GetGeometryBuffer().m_pIndexBuffer.get());
  pipeline.BindVertexShader    (meshData.GetSharedMeshResources().m_pVertexShader.get());
  pipeline.BindPixelShader     (meshData.GetSharedMeshResources().m_pPixelShader.get());
  pipeline.BindTexture         (0U, meshData.GetSharedMeshResources().m_pTexture.get());
  pipeline.BindRasterizerState (meshData.GetSharedMeshResources().m_pRasterizerState.get());

  pipeline.DrawIndexed         (meshData.GetCreateInfo().m_indexCount);
}

void CGeometryPass::BindShaderData(const std::vector<CShaderData*>& shaderData)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();

  size_t vertexShaderIndex = 0U, pixelShaderIndex = 0U;
  for (auto* data : shaderData)
  {
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
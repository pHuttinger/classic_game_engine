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
  m_pRenderTarget_Albedo->Clear(input.m_clearColor);
  m_renderer.GetBackend().GetPipeline().BindRenderTargets(m_renderTargets, m_pDepthBuffer.get());
  m_renderer.GetBackend().GetPipeline().BindSampler(m_pSampler.get());

  for (auto& pMesh : input.m_pMeshes)
  {
    RenderMesh(*pMesh);
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

void CGeometryPass::RenderMesh(CMesh& mesh)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();

  pipeline.BindVertexDescriptor(mesh.GetSharedMeshResources().m_pVertexDescriptor.get());
  pipeline.BindVertexBuffer(mesh.GetGeometryBuffer().m_pVertexBuffer.get());
  pipeline.BindIndexBuffer(mesh.GetGeometryBuffer().m_pIndexBuffer.get());
  pipeline.BindVertexShader(mesh.GetSharedMeshResources().m_pVertexShader.get());
  pipeline.BindPixelShader(mesh.GetSharedMeshResources().m_pPixelShader.get());
  pipeline.DrawIndexed(mesh.GetCreateInfo().m_indexCount);
}
}
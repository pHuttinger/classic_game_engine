//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/GeometryPass.h"

namespace cge::render
{
CGeometryPass::CGeometryPass(CBackend& backend)
  : m_backend(backend)
{
}

TResult CGeometryPass::Initialize()
{
  CGE_TRY(CreateRenderTarget(m_pRenderTarget_Albedo));
  CGE_TRY(CreateDepthBuffer());

  m_renderTargets.push_back(m_pRenderTarget_Albedo.get());

  return TResult::Okay();
}

std::unordered_map<std::string, rhi::IRenderTarget*> CGeometryPass::Execute(const CFrameInput& input) const
{
  m_pRenderTarget_Albedo->Clear();

  m_backend.GetPipeline().BindRenderTargets(m_renderTargets, m_pDepthBuffer.get());

  return
  {
    { "Albedo", m_pRenderTarget_Albedo.get() }
  };
}

TResult CGeometryPass::CreateRenderTarget(std::unique_ptr<rhi::IRenderTarget>& renderTarget)
{
  rhi::TSurfaceCreateInfo surfaceCreateInfo = m_backend.GetSurface().GetCreateInfo();
  rhi::TRenderTargetCreateInfo createInfo
  {
    .m_width  = surfaceCreateInfo.m_width,
    .m_height = surfaceCreateInfo.m_height  
  };

  return m_backend.CreateRenderTarget(createInfo, renderTarget);
}

TResult CGeometryPass::CreateDepthBuffer()
{
  rhi::TSurfaceCreateInfo surfaceCreateInfo = m_backend.GetSurface().GetCreateInfo();
  rhi::TDepthBufferCreateInfo createInfo
  {
    .m_width  = surfaceCreateInfo.m_width,
    .m_height = surfaceCreateInfo.m_height
  };

  return m_backend.CreateDepthBuffer(createInfo, m_pDepthBuffer);
}
}
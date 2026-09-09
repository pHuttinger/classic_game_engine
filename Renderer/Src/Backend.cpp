//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Backend.h"

namespace cge::render
{
TResult CBackend::Create(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(rhi::CreateInstance(createInfo, m_pInstance));

  rhi::TSurfaceCreateInfo surfaceCreateInfo
  {
    .m_width  = createInfo.m_width,
    .m_height = createInfo.m_height
  };

  CGE_TRY(m_pInstance->CreateSurface(surfaceCreateInfo, m_pSurface));

  m_pPipeline = m_pInstance->CreatePipeline();

  return TResult::Okay();
}

TResult CBackend::CreateRenderTarget(const rhi::TRenderTargetCreateInfo& createInfo, std::unique_ptr<rhi::IRenderTarget>& pRenderTarget)
{
  return m_pInstance->CreateRenderTarget(createInfo, pRenderTarget);  
}

TResult CBackend::CreateDepthBuffer(const rhi::TDepthBufferCreateInfo& createInfo, std::unique_ptr<rhi::IDepthBuffer>& pDepthBuffer)
{
  return m_pInstance->CreateDepthBuffer(createInfo, pDepthBuffer);
}
}

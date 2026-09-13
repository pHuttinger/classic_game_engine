//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Backend.h"

namespace cge::render
{
TResult CBackend::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(rhi::CreateInstance(createInfo, m_pInstance));

  rhi::TSurfaceCreateInfo surfaceCreateInfo
  {
    .m_width  = createInfo.m_width,
    .m_height = createInfo.m_height
  };

  CGE_TRY(m_pInstance->CreateSurface(surfaceCreateInfo, m_pSurface));

  m_pPipeline = m_pInstance->CreatePipeline();
  m_pPipeline->SetVertexTopology(rhi::EVertexTopology::TriangleList);

  return TResult::Okay();
}
}

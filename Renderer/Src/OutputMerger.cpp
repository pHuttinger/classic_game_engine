//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/OutputMerger.h"

namespace cge::render
{
COutputMerger::COutputMerger(CBackend& backend)
  : m_backend(backend)
{
}

TResult COutputMerger::Initialize()
{
  // Create VertexShader
  {
    rhi::TVertexShaderCreateInfo createInfo
    {
      .m_filename = m_backend.GetInstance().GetShaderFilename("VS_RenderTarget")
    };
    CGE_TRY(m_backend.GetInstance().CreateVertexShader(createInfo, m_renderResources.m_pVertexShader));
  }

  // Create PixelShader
  {
    rhi::TPixelShaderCreateInfo createInfo
    {
      .m_filename = m_backend.GetInstance().GetShaderFilename("PS_RenderTarget")
    };
    CGE_TRY(m_backend.GetInstance().CreatePixelShader(createInfo, m_renderResources.m_pPixelShader));
  }

  return TResult::Okay();
}

void COutputMerger::Merge(std::vector<rhi::IRenderTarget*>& renderGraphOutput)
{
  m_backend.GetPipeline().BindShaderResources(renderGraphOutput);
}
}
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

void COutputMerger::MergeAndRender(std::vector<rhi::IRenderTarget*>& renderGraphOutput)
{
  m_backend.GetPipeline().BindVertexShader(m_renderResources.m_pVertexShader.get());
  m_backend.GetPipeline().BindPixelShader(m_renderResources.m_pPixelShader.get());
  m_backend.GetPipeline().BindShaderResources(renderGraphOutput);
  //m_backend.GetPipeline().BindSampler(m_renderResources.m_pSampler.get());
  //m_backend.GetPipeline().BindVertexDescriptor(m_renderResources.m_pVertexDescriptor.get());
  //m_backend.GetPipeline().BindVertexBuffer(m_renderResources.m_pVertexBuffer.get());
  //m_backend.GetPipeline().BindIndexBuffer(m_renderResources.m_pIndexBuffer.get());
  //m_backend.GetPipeline().DrawIndexed(m_indexCount);
}
}
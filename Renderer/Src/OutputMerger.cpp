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

  //Create VertexBuffer
  {
    TOutputMergerVertex vertices[] =
    {
        TOutputMergerVertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
        TOutputMergerVertex(-0.5f,  0.5f, 0.5f, 0.0f, 0.0f),
        TOutputMergerVertex( 0.5f,  0.5f, 0.5f, 0.0f, 0.0f),
        TOutputMergerVertex( 0.5f, -0.5f, 0.5f, 0.0f, 0.0f),
    };

    uint32_t indices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

    rhi::TBufferCreateInfo vertexBufferCreateInfo
    {
      .m_usage             = rhi::EBufferUsage::Default,
      .m_bufferType        = rhi::EBufferType::VertexBuffer,
      .m_bufferDestination = rhi::EBufferDestination::VertexShader,
      .m_size              = sizeof(vertices),
      .m_pData             = vertices,
    };

    rhi::TBufferCreateInfo indexBufferCreateInfo
    {
      .m_usage             = rhi::EBufferUsage::Default,
      .m_bufferType        = rhi::EBufferType::IndexBuffer,
      .m_bufferDestination = rhi::EBufferDestination::VertexShader,
      .m_size              = sizeof(indices),
      .m_pData             = indices,
    };

    CGE_TRY(m_backend.GetInstance().CreateBuffer(vertexBufferCreateInfo, m_renderResources.m_pVertexBuffer));
    CGE_TRY(m_backend.GetInstance().CreateBuffer(indexBufferCreateInfo , m_renderResources.m_pIndexBuffer));
  }

  {
    rhi::TVertexDescriptorCreateInfo createInfo
    {
      .pVertexShader = m_renderResources.m_pVertexShader.get()
    };

    CGE_TRY(m_backend.GetInstance().CreateVertexDescriptor(createInfo, m_renderResources.m_pVertexDescriptor));
  }

  {
    CGE_TRY(m_backend.GetInstance().CreateSampler(m_renderResources.m_pSampler));
  }

  return TResult::Okay();
}

void COutputMerger::MergeAndRender(std::vector<rhi::IRenderTarget*>& renderGraphOutput)
{
  m_backend.GetSurface().Clear();
  m_backend.GetPipeline().BindVertexShader(m_renderResources.m_pVertexShader.get());
  m_backend.GetPipeline().BindPixelShader(m_renderResources.m_pPixelShader.get());
  m_backend.GetPipeline().BindShaderResources(renderGraphOutput);
  m_backend.GetPipeline().BindSampler(m_renderResources.m_pSampler.get());
  m_backend.GetPipeline().BindVertexDescriptor(m_renderResources.m_pVertexDescriptor.get());
  m_backend.GetPipeline().BindVertexBuffer(m_renderResources.m_pVertexBuffer.get());
  m_backend.GetPipeline().BindIndexBuffer(m_renderResources.m_pIndexBuffer.get());
  m_backend.GetPipeline().DrawIndexed(6U);
}
}
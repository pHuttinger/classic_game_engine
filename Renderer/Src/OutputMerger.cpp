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
  CGE_TRY(CreateVertexShader());
  CGE_TRY(CreatePixelShader());
  CGE_TRY(CreateVertexDescriptor());
  CGE_TRY(CreateVertexBuffer());
  CGE_TRY(CreateIndexBuffer());
  CGE_TRY(CreateSampler());

  return TResult::Okay();
}

void COutputMerger::MergeAndRender(std::vector<rhi::IRenderTarget*>& renderGraphOutput)
{
  m_backend.GetSurface().SetAsRenderTarget();

  m_backend.GetPipeline().BindShaderResources (renderGraphOutput);
  m_backend.GetPipeline().BindVertexShader    (m_renderResources.m_pVertexShader.get());
  m_backend.GetPipeline().BindPixelShader     (m_renderResources.m_pPixelShader.get());
  m_backend.GetPipeline().BindSampler         (m_renderResources.m_pSampler.get());
  m_backend.GetPipeline().BindVertexDescriptor(m_renderResources.m_pVertexDescriptor.get());
  m_backend.GetPipeline().BindVertexBuffer    (m_renderResources.m_pVertexBuffer.get());
  m_backend.GetPipeline().BindIndexBuffer     (m_renderResources.m_pIndexBuffer.get());

  m_backend.GetPipeline().DrawIndexed(6U);
}

TResult COutputMerger::CreateVertexShader()
{
  rhi::TVertexShaderCreateInfo createInfo
  {
    .m_filename = m_backend.GetInstance().GetShaderFilename("VS_RenderTarget")
  };
  CGE_TRY(m_backend.GetInstance().CreateVertexShader(createInfo, m_renderResources.m_pVertexShader));
  return TResult::Okay();
}

TResult COutputMerger::CreatePixelShader()
{
  rhi::TPixelShaderCreateInfo createInfo
  {
    .m_filename = m_backend.GetInstance().GetShaderFilename("PS_RenderTarget")
  };
  CGE_TRY(m_backend.GetInstance().CreatePixelShader(createInfo, m_renderResources.m_pPixelShader));
  return TResult::Okay();
}

TResult COutputMerger::CreateVertexDescriptor()
{
  rhi::TVertexDescriptorCreateInfo createInfo
  {
    .pVertexShader = m_renderResources.m_pVertexShader.get(),
    .m_vertexAttributeInfos =
    {
      {rhi::EVertexAttributeUsage::Position, rhi::EVertexAttributeFormat::Float3},
      {rhi::EVertexAttributeUsage::Texcoord, rhi::EVertexAttributeFormat::Float2},
    }
  };
  CGE_TRY(m_backend.GetInstance().CreateVertexDescriptor(createInfo, m_renderResources.m_pVertexDescriptor));
  return TResult::Okay();
}

TResult COutputMerger::CreateVertexBuffer()
{
  TOutputMergerVertex vertices[] =
  {
    TOutputMergerVertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f),
    TOutputMergerVertex(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
    TOutputMergerVertex( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
    TOutputMergerVertex( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f),
  };

  rhi::TBufferCreateInfo vertexBufferCreateInfo
  {
    .m_usage             = rhi::EBufferUsage::Default,
    .m_bufferType        = rhi::EBufferType::VertexBuffer,
    .m_bufferDestination = rhi::EBufferDestination::VertexShader,
    .m_size              = sizeof(vertices),
    .m_pData             = vertices,
    .m_stride            = sizeof(TOutputMergerVertex),
  };

  CGE_TRY(m_backend.GetInstance().CreateBuffer(vertexBufferCreateInfo, m_renderResources.m_pVertexBuffer));
  return TResult::Okay();
}

TResult COutputMerger::CreateIndexBuffer()
{
  uint32_t indices[] =
  {
    0, 1, 2,
    0, 2, 3
  };

  rhi::TBufferCreateInfo indexBufferCreateInfo
  {
    .m_usage             = rhi::EBufferUsage::Default,
    .m_bufferType        = rhi::EBufferType::IndexBuffer,
    .m_bufferDestination = rhi::EBufferDestination::VertexShader,
    .m_size              = sizeof(indices),
    .m_pData             = indices,
  };

  CGE_TRY(m_backend.GetInstance().CreateBuffer(indexBufferCreateInfo, m_renderResources.m_pIndexBuffer));
  return TResult::Okay();
}

TResult COutputMerger::CreateSampler()
{
  CGE_TRY(m_backend.GetInstance().CreateSampler(m_renderResources.m_pSampler));
  return TResult::Okay();
}
}
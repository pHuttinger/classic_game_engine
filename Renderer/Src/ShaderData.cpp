//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/ShaderData.h"
#include "../Inc/Renderer.h"

namespace cge::render
{
CShaderData::CShaderData(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CShaderData::Initialize(const TShaderDataCreateInfo& createInfo)
{
  m_createInfo = createInfo;

  rhi::TBufferCreateInfo bufferCreateInfo
  {
    .m_usage      = rhi::EBufferUsage::Default,
    .m_bufferType = rhi::EBufferType::ConstantBuffer,
    .m_size       = createInfo.m_size
  };

  rhi::IInstance& rhi = m_renderer.GetBackend().GetInstance();

  CGE_TRY(rhi.CreateBuffer(bufferCreateInfo, m_pBuffer));

  return TResult::Okay();
}

void CShaderData::UpdateData(const rhi::TBufferUpdateInfo& updateInfo)
{
  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();
  pipeline.UpdateBuffer(m_pBuffer.get(), updateInfo);
}
}
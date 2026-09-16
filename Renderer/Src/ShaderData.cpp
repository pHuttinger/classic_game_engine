//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/ShaderData.h"

namespace cge::render
{
TResult CShaderData::Initialize(CRenderer& renderer, const TShaderDataCreateInfo& createInfo)
{
  rhi::TBufferCreateInfo bufferCreateInfo
  {
    .m_usage      = rhi::EBufferUsage::Default,
    .m_bufferType = rhi::EBufferType::ConstantBuffer,
    .m_size       = createInfo.m_size
  };

  rhi::IInstance& rhi = renderer.GetBackend().GetInstance();

  CGE_TRY(rhi.CreateBuffer(bufferCreateInfo, m_pBuffer));

  return TResult::Okay();
}

void CShaderData::UpdateData(CRenderer& renderer, const TDataHandle& dataHandle)
{
  rhi::IPipeline& pipeline = renderer.GetBackend().GetPipeline();
  pipeline.UpdateBufferData(m_pBuffer.get(), dataHandle);
}
}
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

  CResourceManager& resourceManager = m_renderer.GetResourceManager();

  CGE_TRY(resourceManager.GetConstantBuffer(createInfo, m_pBuffer));

  return TResult::Okay();
}

void CShaderData::SetData(const TDataHandle& data)
{
  m_data.resize(data.m_size);
  std::memcpy(m_data.data(), data.m_pData, data.m_size);
}

void CShaderData::UpdateBuffer()
{
  rhi::TBufferUpdateInfo updateInfo
  {
    .m_pData = m_data.data()
  };  

  rhi::IPipeline& pipeline = m_renderer.GetBackend().GetPipeline();
  pipeline.UpdateBuffer(m_pBuffer.get(), updateInfo);
}
}
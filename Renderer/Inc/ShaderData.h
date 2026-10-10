//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"

namespace cge::render
{
class CRenderer;

//----------------------------------------------------
// EShaderDataDestination
//----------------------------------------------------
enum class EShaderDataDestination : uint32_t
{
  Vertex,
  Pixel
};

//----------------------------------------------------
// TShaderDataCreateInfo
//----------------------------------------------------
struct TShaderDataCreateInfo final
{
  size_t                 m_size        = 0U;
  EShaderDataDestination m_destination = EShaderDataDestination::Vertex;
};

//----------------------------------------------------
// CShaderData
//----------------------------------------------------
class CShaderData final
{
public:

  CShaderData(CRenderer& renderer);

  TResult Initialize(const TShaderDataCreateInfo& createInfo);

  void SetData(const TDataHandle& data);
  void UpdateBuffer();

  TShaderDataCreateInfo& GetCreateInfo() { return m_createInfo; }
  rhi::IBuffer* GetBuffer() { return m_pBuffer.get(); }

private:

  CRenderer& m_renderer;
  TShaderDataCreateInfo m_createInfo;
  std::shared_ptr<rhi::IBuffer> m_pBuffer;
  std::vector<unsigned char> m_data;
};
}
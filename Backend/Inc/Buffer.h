//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//----------------------------------------------------
// EBufferUsage
//----------------------------------------------------
enum class EBufferUsage
{
  Default,
  Dynamic,
};

//----------------------------------------------------
// EBufferType
//----------------------------------------------------
enum class EBufferType
{
  VertexBuffer,
  IndexBuffer,
  ConstantBuffer,
};

//----------------------------------------------------
// EBufferDestination
//----------------------------------------------------
enum class EBufferDestination
{
  VertexShader,
  PixelShader
};

//----------------------------------------------------
// TBufferCreateInfo
//----------------------------------------------------
struct TBufferCreateInfo final
{
  EBufferUsage       m_usage             = EBufferUsage::Default;
  EBufferType        m_bufferType        = EBufferType::VertexBuffer;
  EBufferDestination m_bufferDestination = EBufferDestination::VertexShader;
  size_t             m_size              = 0U;
  void*              m_pData             = nullptr;
};

//----------------------------------------------------
// TBufferCreateInfo
//----------------------------------------------------
class IBuffer
{
public:

  virtual ~IBuffer() = default;

  virtual TResult Initialize(const TBufferCreateInfo& createInfo) = 0;
};
}
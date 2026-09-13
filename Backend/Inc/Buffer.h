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
  Undefined,
  Default,
  Dynamic,
};

//----------------------------------------------------
// EBufferType
//----------------------------------------------------
enum class EBufferType
{
  Undefined,
  VertexBuffer,
  IndexBuffer,
  ConstantBuffer,
};

//----------------------------------------------------
// EBufferDestination
//----------------------------------------------------
enum class EBufferDestination
{
  Undefined,
  VertexShader,
  PixelShader
};

//----------------------------------------------------
// TBufferCreateInfo
//----------------------------------------------------
struct TBufferCreateInfo final
{
  EBufferUsage       m_usage             = EBufferUsage::Undefined;
  EBufferType        m_bufferType        = EBufferType::Undefined;
  EBufferDestination m_bufferDestination = EBufferDestination::Undefined;
  size_t             m_size              = 0U;
  void*              m_pData             = nullptr;
  size_t             m_stride            = 0U;
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
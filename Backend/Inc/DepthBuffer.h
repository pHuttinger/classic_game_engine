//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//----------------------------------------------------
// TDepthBufferCreateInfo
//----------------------------------------------------
struct TDepthBufferCreateInfo final
{
  uint16_t m_width  = 800U;
  uint16_t m_height = 600U;
};

//----------------------------------------------------
// TDepthBufferCreateInfo
//----------------------------------------------------
class IDepthBuffer
{
public:

  virtual ~IDepthBuffer() = default;

  virtual TResult Initialize(const TDepthBufferCreateInfo& createInfo) = 0;
};
}
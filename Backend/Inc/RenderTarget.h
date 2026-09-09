//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//----------------------------------------------------
// TRenderTargetCreateInfo
//----------------------------------------------------
struct TRenderTargetCreateInfo final
{
  uint16_t m_width = 800U;
  uint16_t m_height = 600U;
};

//----------------------------------------------------
// TRenderTargetCreateInfo
//----------------------------------------------------
class IRenderTarget
{
public:

  virtual ~IRenderTarget() = default;

  virtual TResult Initialize(const TRenderTargetCreateInfo& createInfo) = 0;

  virtual void Clear() = 0;
};
}
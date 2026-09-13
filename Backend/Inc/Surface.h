//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//----------------------------------------------------
// TSurfaceCreateInfo
//----------------------------------------------------
struct TSurfaceCreateInfo final
{
  uint16_t m_width  = 800U;
  uint16_t m_height = 600U;
};

//----------------------------------------------------
// TSurfaceCreateInfo
//----------------------------------------------------
class ISurface
{
public:

  virtual ~ISurface() = default;

  virtual TResult Initialize(const TSurfaceCreateInfo& createInfo) = 0;

  virtual void Clear() = 0;
  virtual void SetAsRenderTarget() = 0;

  virtual TSurfaceCreateInfo GetCreateInfo() const = 0;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Surface.h"

namespace cge::rhi
{
class IPipeline
{
public:

  virtual ~IPipeline() = default;

  virtual void Clear(ISurface& surface) = 0;
  virtual void Present() = 0;
};
}
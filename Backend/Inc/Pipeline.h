//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

namespace cge::rhi
{
class IPipeline
{
public:

  virtual ~IPipeline() = default;

  virtual void Clear() = 0;
  virtual void Present() = 0;
};
}
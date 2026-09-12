//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
class ISampler
{
public:

  virtual ~ISampler() = default;

  virtual TResult Initialize() = 0;
};
}
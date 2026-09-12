//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "FrameInput.h"

namespace cge::render
{
class IRenderPass
{
public:

  virtual ~IRenderPass() = default;

  virtual std::vector<rhi::IRenderTarget*> Execute(const CFrameInput& input) const = 0;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "RenderTarget.h"
#include "DepthBuffer.h"

namespace cge::rhi
{
class IPipeline
{
public:

  virtual ~IPipeline() = default;

  virtual void Present() = 0;
  virtual void BindRenderTargets(const std::vector<IRenderTarget*>& renderTargets, IDepthBuffer* depthBuffer) = 0;
  virtual void BindShaderResources(const std::vector<IRenderTarget*>& renderTargets) = 0;
};
}
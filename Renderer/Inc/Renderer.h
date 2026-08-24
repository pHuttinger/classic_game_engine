//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderGraph.h"

namespace cge::render
{
class CRenderer final
{
public:

  CRenderer();

  TResult Initialize(const rhi::TCreateInfo& createInfo);
  void RenderFrame(const CFrameInput& input);

private:

  void Present();

  CBackend m_backend;
  CRenderGraph m_renderGraph;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderPass.h"

namespace cge::render
{
class CRenderer;

class CRenderGraph final
{
public:

  CRenderGraph(CRenderer& renderer);

  TResult Initialize();

  std::vector<rhi::IRenderTarget*> Execute(const CFrameInput& input) const;

private:

  TResult CreateGeometryPass();

  CRenderer& m_renderer;
  std::vector<std::unique_ptr<IRenderPass>> m_renderPasses;
};
}
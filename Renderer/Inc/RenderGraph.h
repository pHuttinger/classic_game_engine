//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderPass.h"

namespace cge::render
{
class CRenderGraph final
{
public:

  CRenderGraph(CBackend& backend);

  TResult Initialize();

  std::vector<rhi::IRenderTarget*> Execute(const CFrameInput& input) const;

private:

  TResult CreateGeometryPass();

  CBackend& m_backend;
  std::vector<std::unique_ptr<IRenderPass>> m_renderPasses;
};
}
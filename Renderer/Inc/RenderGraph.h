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

  void Execute(const CFrameInput& input) const;

private:

  CBackend& m_backend;
  std::vector<std::unique_ptr<IRenderPass>> m_renderPasses;
};
}
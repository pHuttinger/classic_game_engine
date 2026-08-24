//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/RenderGraph.h"

namespace cge::render
{
CRenderGraph::CRenderGraph(CBackend& backend)
  : m_backend(backend)
{
}

void CRenderGraph::Execute(const CFrameInput& input) const
{
  for (auto& renderPass : m_renderPasses)
  {
    renderPass->Execute(input);
  }
}
}

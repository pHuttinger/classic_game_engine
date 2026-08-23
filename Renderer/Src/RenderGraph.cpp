//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/RenderGraph.h"

namespace cge::render
{
void CRenderGraph::Create(rhi::IInstance* pBackend)
{
  m_pBackend = pBackend;
}

void CRenderGraph::Execute(const CFrameInput& input) const
{
  for (auto& renderPass : m_renderPasses)
  {
    renderPass->Execute(input);
  }
}
}

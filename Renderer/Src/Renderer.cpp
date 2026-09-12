/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
  : m_renderGraph(m_backend)
  , m_outputMerger(m_backend)
{
}

TResult CRenderer::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_backend.Create(createInfo));
  CGE_MILESTONE("backend initialized...");

  CGE_TRY(m_renderGraph.Initialize());
  CGE_MILESTONE("renderGraph initialized...");

  CGE_TRY(m_outputMerger.Initialize());
  CGE_MILESTONE("outputMerger initialized...");

  return TResult::Okay();
}

void CRenderer::RenderFrame(const CFrameInput& input)
{
  m_backend.GetSurface().Clear();

  auto renderTargets = m_renderGraph.Execute(input);
  m_outputMerger.MergeAndRender(renderTargets);

  m_backend.GetPipeline().Present();
}
}

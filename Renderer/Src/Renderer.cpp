/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
  : m_renderGraph(*this)
  , m_outputMerger(m_backend)
  , m_resourceManager(m_backend)
  , m_meshFactory(*this)
{
}

TResult CRenderer::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_backend.Initialize(createInfo));
  CGE_MILESTONE("backend created...");

  CGE_TRY(m_renderGraph.Initialize());
  CGE_MILESTONE("renderGraph created...");

  CGE_TRY(m_outputMerger.Initialize());
  CGE_MILESTONE("outputMerger created...");

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

/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
  : m_renderGraph(m_backend)
{
}

TResult CRenderer::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_backend.Create(createInfo));
  CGE_MILESTONE("backend initialized...");

  return TResult::Okay();
}

void CRenderer::RenderFrame(const CFrameInput& input)
{
  m_renderGraph.Execute(input);
  Present();
}

void CRenderer::Present()
{
}

//glm::vec2 CRenderer::GetViewportSize() const
//{
//  return m_backend.GetRenderTarget().GetSize();
//}
}
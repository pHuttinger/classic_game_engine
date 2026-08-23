/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
{
}

TResult CRenderer::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(rhi::CreateInstance(createInfo, m_pBackend));
  CGE_MILESTONE("backend initialized...");

  m_renderGraph.Create(m_pBackend.get());

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
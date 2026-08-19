/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
  //: m_frameSystem(m_backend)
  //, m_renderGraph(m_backend)
{
}

TResult CRenderer::Initialize(const TBackendCreateInfo& createInfo)
{
  CGE_TRY(m_backend.Initialize(createInfo));
  CGE_MILESTONE("backend initialized...");

  //CGE_TRY(m_frameSystem.Initialize());
  //CGE_MILESTONE("frameSystem initialized...");

  //CGE_TRY(m_renderGraph.Create());

  return TResult::Okay();
}

//void CRenderer::RenderFrame(const CRenderFrameInput& input)
//{
//  TFrameData frameData = m_frameSystem.BeginFrame();
//  m_renderGraph.Execute(frameData, input);
//  m_frameSystem.EndFrame(frameData);
//}
//
//glm::vec2 CRenderer::GetViewportSize() const
//{
//  return m_backend.GetRenderTarget().GetSize();
//}
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
//#include "FrameSystem.h"
//#include "RenderGraph.h"

namespace cge::render
{
class RENDER_API CRenderer final
{
public:

  CRenderer();

  TResult Initialize(const TBackendCreateInfo& createInfo);
  //void RenderFrame(const CRenderFrameInput& input);
  //glm::vec2 GetViewportSize() const;

  //CBackend& GetBackend() { return m_backend; };
  //CFrameSystem& GetFrameSystem() { return m_frameSystem; }

private:

  CBackend m_backend;
  //CFrameSystem m_frameSystem;
  //CRenderGraph m_renderGraph;
};
}
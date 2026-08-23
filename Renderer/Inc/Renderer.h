//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>
#include "RenderGraph.h"

namespace cge::render
{
class CRenderer final
{
public:

  CRenderer();

  TResult Initialize(const rhi::TCreateInfo& createInfo);
  void RenderFrame(const CFrameInput& input);
  //glm::vec2 GetViewportSize() const;

private:

  void Present();

  std::unique_ptr<rhi::IInstance> m_pBackend;
  CRenderGraph m_renderGraph;
};
}
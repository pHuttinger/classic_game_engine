////////////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>
#include "StaticMesh.h"

namespace cge
{
class CRenderProxy final
{
public:

  CRenderProxy();

  TResult Initialize(const rhi::TCreateInfo& createInfo);

  void RenderFrame(const float engineTime);
  void AddDrawCall(const render::TDrawCall& drawCall);

  render::CRenderer& GetRenderer() { return m_renderer; }

private:

  render::CRenderer m_renderer;
  render::CFrameInput m_frameInput;
};
}
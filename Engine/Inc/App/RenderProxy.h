////////////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>

namespace cge
{
class CRenderProxy final
{
public:

  CRenderProxy();

  TResult Initialize(const rhi::TCreateInfo& createInfo);

  void RenderFrame();

private:

  render::CRenderer m_renderer;
};
}
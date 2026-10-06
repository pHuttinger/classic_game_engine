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

  TResult CreateStaticMesh(const render::TMeshCreateInfo& createInfo, std::unique_ptr<CStaticMesh>& pStaticMesh);

  void RenderFrame();

private:

  render::CRenderer m_renderer;
  render::CFrameInput m_frameInput;
  //TODO remove!
  std::unique_ptr<CStaticMesh> m_pStaticMesh;
};
}
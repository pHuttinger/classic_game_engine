/////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Renderer.h"

namespace cge::render
{
CRenderer::CRenderer()
  : m_renderGraph(*this)
  , m_composer(m_backend)
  , m_resourceManager(m_backend)
  , m_drawItemFactory(*this)
{
}

TResult CRenderer::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_backend.Initialize(createInfo));
  CGE_MILESTONE("backend created...");

  CGE_TRY(m_renderGraph.Initialize());
  CGE_MILESTONE("renderGraph created...");

  CGE_TRY(m_composer.Initialize());
  CGE_MILESTONE("composer created...");

  return TResult::Okay();
}

void CRenderer::RenderFrame(const CFrameInput& input)
{
  m_backend.GetSurface().Clear(input.m_clearColor);

  TComposerInput composerInput
  {
    .m_channels        = m_renderGraph.Execute(input),
    .m_pixelShaderData = 
    {
      .m_lightDirection = input.m_lightDirection,
      .m_cameraPosition = input.m_cameraPosition,
      .m_fogColor       = glm::vec3(1.0f, 0.0f, 0.0f)//input.m_clearColor,
    },
  };

  m_composer.ComposeFrame(composerInput);

  m_backend.GetPipeline().Present();
}
}

/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../Inc/RenderProxy.h"

namespace cge
{
CRenderProxy::CRenderProxy()
{
}

TResult CRenderProxy::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_renderer.Initialize(createInfo));

  return TResult::Okay();
}

void CRenderProxy::RenderFrame(const float engineTime)
{
  m_renderer.RenderFrame(m_frameInput);
  m_frameInput.Reset();
}

void CRenderProxy::AddDrawCall(const render::TDrawCall& drawCall)
{
  m_frameInput.AddDrawCall(drawCall);
}
}
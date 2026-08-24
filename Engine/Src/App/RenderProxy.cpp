/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/App/RenderProxy.h"

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

void CRenderProxy::RenderFrame()
{
  m_renderer.RenderFrame(CFrameInput());
}
}
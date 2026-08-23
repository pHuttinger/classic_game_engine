/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/App/RenderProxy.h"

namespace cge
{
CRenderProxy::CRenderProxy()
  //: m_staticMeshFactory(m_renderer)
{
}

TResult CRenderProxy::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_renderer.Initialize(createInfo));

  return TResult::Okay();
}

void CRenderProxy::Open()
{
  //m_renderFrameInput.Clear();
}

void CRenderProxy::Present()
{
  //m_renderer.RenderFrame(m_renderFrameInput);
}

//void CRenderProxy::SetViewInfo(const rendering::TRenderFrameViewInfo& viewInfo)
//{
//  m_renderFrameInput.SetViewInfo(viewInfo);
//}
//
//void CRenderProxy::FrameAddStaticMesh(rendering::CStaticMesh* pStaticMesh)
//{
//  m_renderFrameInput.AddStaticMesh(pStaticMesh);
//}
}
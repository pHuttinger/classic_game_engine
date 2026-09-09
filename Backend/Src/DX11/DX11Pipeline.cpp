//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Pipeline.h"
#include "../../Inc/DX11/DX11RenderTarget.h"
#include "../../Inc/DX11/DX11DepthBuffer.h"

namespace cge::rhi::dx11
{
CPipeline::CPipeline(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

void CPipeline::Present()
{
  m_instance.GetSwapChain()->Present(0, 0);
}

void CPipeline::BindRenderTargets(const std::vector<IRenderTarget*>& renderTargets, IDepthBuffer* depthBuffer)
{
  CDepthBuffer* pDepthBuffer = static_cast<CDepthBuffer*>(depthBuffer);

  std::vector<ID3D11RenderTargetView*> renderTargetViews;

  for (IRenderTarget* renderTarget : renderTargets)
  {
    renderTargetViews.push_back(static_cast<CRenderTarget*>(renderTarget)->GetRenderTargetView());
  }

  m_instance.GetDeviceContext()->OMSetRenderTargets(renderTargets.size(), renderTargetViews.data(), pDepthBuffer->GetDepthStencilView());
}
}
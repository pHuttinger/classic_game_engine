//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Pipeline.h"
#include "../../Inc/DX11/DX11RenderTarget.h"
#include "../../Inc/DX11/DX11DepthBuffer.h"
#include "../../Inc/DX11/DX11VertexShader.h"
#include "../../Inc/DX11/DX11PixelShader.h"

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

void CPipeline::BindVertexShader(IVertexShader* vertexShader)
{
  CVertexShader* pVertexShader = static_cast<CVertexShader*>(vertexShader);
  m_instance.GetDeviceContext()->VSSetShader(pVertexShader->GetVertexShader(), nullptr, 0);
}

void CPipeline::BindPixelShader(IPixelShader* pixelShader)
{
  CPixelShader* pPixelShader = static_cast<CPixelShader*>(pixelShader);
  m_instance.GetDeviceContext()->PSSetShader(pPixelShader->GetPixelShader(), nullptr, 0);
}

void CPipeline::BindShaderResources(const std::vector<IRenderTarget*>& renderTargets)
{
  std::vector<ID3D11ShaderResourceView*> shaderResourceViews;
  for (IRenderTarget* renderTarget : renderTargets)
  {
    shaderResourceViews.push_back(static_cast<CRenderTarget*>(renderTarget)->GetShaderResourceView());
  }
  m_instance.GetDeviceContext()->PSSetShaderResources(0U, shaderResourceViews.size(), shaderResourceViews.data());
}
}
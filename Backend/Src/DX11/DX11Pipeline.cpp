//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Pipeline.h"
#include "../../Inc/DX11/DX11RenderTarget.h"
#include "../../Inc/DX11/DX11DepthBuffer.h"
#include "../../Inc/DX11/DX11VertexShader.h"
#include "../../Inc/DX11/DX11PixelShader.h"
#include "../../Inc/DX11/DX11Sampler.h"
#include "../../Inc/DX11/DX11Buffer.h"
#include "../../Inc/DX11/DX11VertexDescriptor.h"

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

void CPipeline::BindSampler(ISampler* sampler)
{
  CSampler* pSampler = static_cast<CSampler*>(sampler);
  ID3D11SamplerState* samplers[] = { pSampler->GetSamplerState() };
  m_instance.GetDeviceContext()->PSSetSamplers(0U, 1U, samplers);
}

void CPipeline::BindVertexDescriptor(IVertexDescriptor* vertexDescriptor)
{
  CVertexDescriptor* pVertexDescriptor = static_cast<CVertexDescriptor*>(vertexDescriptor);
  m_instance.GetDeviceContext()->IASetInputLayout(pVertexDescriptor->GetInputLayout());
}

void CPipeline::BindVertexBuffer(IBuffer* vertexBuffer)
{
  CBuffer* pBuffer = static_cast<CBuffer*>(vertexBuffer);
  UINT stride = pBuffer->GetCreateInfo().m_stride;
  UINT offset = 0;
  ID3D11Buffer* buffers[] = { pBuffer->GetBuffer() };
  m_instance.GetDeviceContext()->IASetVertexBuffers(0U, 1U, buffers, &stride, &offset);
}

void CPipeline::BindIndexBuffer(IBuffer* indexBuffer)
{
  CBuffer* pBuffer = static_cast<CBuffer*>(indexBuffer);
  m_instance.GetDeviceContext()->IASetIndexBuffer(pBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void CPipeline::DrawIndexed(uint32_t indexCount)
{
  m_instance.GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}
}
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
#include "../../Inc/DX11/DX11RasterizerState.h"
#include "../../Inc/DX11/DX11Texture.h"

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

void CPipeline::SetVertexTopology(EVertexTopology topology)
{
  D3D11_PRIMITIVE_TOPOLOGY dx11Topology;
  switch (topology)
  {
    case EVertexTopology::PointList    : dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST    ; break;
    case EVertexTopology::LineList     : dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST     ; break;
    case EVertexTopology::LineStrip    : dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP    ; break;
    case EVertexTopology::TriangleList : dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ; break;
    case EVertexTopology::TriangleStrip: dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP; break;
    default                            : dx11Topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED    ; break;
  }
  m_instance.GetDeviceContext()->IASetPrimitiveTopology(dx11Topology);
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

void CPipeline::BindPixelShaderResources(const std::vector<IRenderTarget*>& renderTargets)
{
  std::vector<ID3D11ShaderResourceView*> shaderResourceViews;
  for (IRenderTarget* renderTarget : renderTargets)
  {
    shaderResourceViews.push_back(static_cast<CRenderTarget*>(renderTarget)->GetShaderResourceView());
  }
  m_instance.GetDeviceContext()->PSSetShaderResources(0U, shaderResourceViews.size(), shaderResourceViews.data());
}

void CPipeline::BindPixelShaderResources(size_t slot, IBuffer* pBuffer)
{
  ID3D11Buffer* buffer = static_cast<CBuffer*>(pBuffer)->GetBuffer();
  m_instance.GetDeviceContext()->PSSetConstantBuffers(slot, 1U, &buffer);
}

void CPipeline::BindVertexShaderResources(size_t slot, IBuffer* pBuffer)
{
  ID3D11Buffer* buffer = static_cast<CBuffer*>(pBuffer)->GetBuffer();
  m_instance.GetDeviceContext()->VSSetConstantBuffers(slot, 1U, &buffer);
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

void CPipeline::UpdateBuffer(IBuffer* buffer, const TBufferUpdateInfo& updateInfo)
{
  CBuffer* pBuffer = static_cast<CBuffer*>(buffer);
  m_instance.GetDeviceContext()->UpdateSubresource(pBuffer->GetBuffer(), 0U, nullptr, updateInfo.m_pData, 0U, 0U);
}

void CPipeline::BindRasterizerState(IRasterizerState* rasterizerState)
{
  CRasterizerState* pRasterizerState = static_cast<CRasterizerState*>(rasterizerState);
  m_instance.GetDeviceContext()->RSSetState(pRasterizerState->GetRasterizerState());
}

void CPipeline::BindTexture(size_t slot, ITexture* texture)
{
  CTexture* pTexture = static_cast<CTexture*>(texture);
  ID3D11ShaderResourceView* shaderResourceViews[] = { pTexture->GetShaderResourceView() };
  m_instance.GetDeviceContext()->PSSetShaderResources(slot, 1U, shaderResourceViews);
}

void CPipeline::DrawIndexed(uint32_t indexCount)
{
  m_instance.GetDeviceContext()->DrawIndexed(indexCount, 0, 0);
}
}
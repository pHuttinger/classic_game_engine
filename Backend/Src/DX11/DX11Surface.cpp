//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Surface.h"

namespace cge::rhi::dx11
{
CSurface::CSurface(IInstance& instance)
  : m_instance(dynamic_cast<CInstance&>(instance))
{
}

TResult CSurface::Initialize(const TSurfaceCreateInfo& createInfo)
{
  CGE_TRY(InitializeRenderTargetView(createInfo));
  CGE_TRY(InitializeDepthBuffer(createInfo));
  return TResult::Okay();
}

void CSurface::Clear()
{
  m_instance.GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
  m_instance.GetDeviceContext()->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  m_instance.GetDeviceContext()->OMSetRenderTargets(1, &m_pRenderTargetView.Get(), m_pDepthStencilView.Get());
}

TResult CSurface::InitializeRenderTargetView(const TSurfaceCreateInfo& createInfo)
{
  ID3D11Texture2D* backBuffer = nullptr;

  m_instance.GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
  if (backBuffer == nullptr)
  {
    return TResult::Error("Failed to get BackBuffer");
  }

  HRESULT hr = m_instance.GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView.Get());

  backBuffer->Release();

  CGE_HRESULT_CHECK(hr, "Can't create RenderTargetView");

  return TResult::Okay();
}

TResult CSurface::InitializeDepthBuffer(const TSurfaceCreateInfo& createInfo)
{
  D3D11_TEXTURE2D_DESC depthStencilDesc{};
  depthStencilDesc.Width              = createInfo.m_width;
  depthStencilDesc.Height             = createInfo.m_height;
  depthStencilDesc.MipLevels          = 1;
  depthStencilDesc.ArraySize          = 1;
  depthStencilDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilDesc.SampleDesc.Count   = 1;
  depthStencilDesc.SampleDesc.Quality = 0;
  depthStencilDesc.Usage              = D3D11_USAGE_DEFAULT;
  depthStencilDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
  depthStencilDesc.CPUAccessFlags     = 0;
  depthStencilDesc.MiscFlags          = 0;

  HRESULT hr = m_instance.GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, &m_pDepthBuffer.Get());

  CGE_HRESULT_CHECK(hr, "failed to create depthBuffer");

  hr = m_instance.GetDevice()->CreateDepthStencilView(m_pDepthBuffer.Get(), nullptr, &m_pDepthStencilView.Get());

  CGE_HRESULT_CHECK(hr, "failed to create depthStencilView");

  return TResult::Okay();
}
}
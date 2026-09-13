//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Surface.h"

namespace cge::rhi::dx11
{
CSurface::CSurface(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CSurface::Initialize(const TSurfaceCreateInfo& createInfo)
{
  m_createInfo = createInfo;

  CGE_TRY(InitializeRenderTargetView(createInfo));

  return TResult::Okay();
}

void CSurface::Clear()
{
  m_instance.GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

void CSurface::SetAsRenderTarget()
{
  ID3D11RenderTargetView* renderTargets[] = { m_pRenderTargetView.Get() };
  m_instance.GetDeviceContext()->OMSetRenderTargets(1U, renderTargets, nullptr);

  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0.0f;
  viewport.TopLeftY = 0.0f;
  viewport.Width    = m_createInfo.m_width;
  viewport.Height   = m_createInfo.m_height;

  m_instance.GetDeviceContext()->RSSetViewports(1U, &viewport);
}

TResult CSurface::InitializeRenderTargetView(const TSurfaceCreateInfo& createInfo)
{
  ID3D11Texture2D* backBuffer = nullptr;
  m_instance.GetSwapChain()->GetBuffer(0U, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
  if (backBuffer == nullptr)
  {
    return TResult::Error("Failed to get BackBuffer");
  }

  HRESULT hr = m_instance.GetDevice()->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView.Get());
  backBuffer->Release();
  CGE_HRESULT_CHECK(hr, "Can't create RenderTargetView");

  return TResult::Okay();
}
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Surface.h"

namespace cge::rhi::dx11
{
CSurface::CSurface(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
  , m_viewport()
{
}

TResult CSurface::Initialize(const TSurfaceCreateInfo& createInfo)
{
  m_createInfo = createInfo;

  CGE_TRY(InitializeRenderTargetView(createInfo));
  InitializeViewport(createInfo);

  return TResult::Okay();
}

void CSurface::Clear(const glm::vec4& color)
{
  m_instance.GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), D3DXCOLOR(color.r, color.g, color.b, color.a));
}

void CSurface::SetAsRenderTarget()
{
  ID3D11RenderTargetView* renderTargets[] = { m_pRenderTargetView.Get() };
  m_instance.GetDeviceContext()->OMSetRenderTargets(1U, renderTargets, nullptr);
  m_instance.GetDeviceContext()->RSSetViewports(1U, &m_viewport);
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

void CSurface::InitializeViewport(const TSurfaceCreateInfo& createInfo)
{
  ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));

  m_viewport.TopLeftX = 0.0f;
  m_viewport.TopLeftY = 0.0f;
  m_viewport.Width    = m_createInfo.m_width;
  m_viewport.Height   = m_createInfo.m_height;
}
}
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
}
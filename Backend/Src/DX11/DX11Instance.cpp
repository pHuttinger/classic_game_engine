/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Instance.h"

namespace cge::rhi::dx11
{
CInstance::~CInstance()
{
  m_pSwapChain.Get()->SetFullscreenState(false, nullptr);
}

TResult CInstance::Create(const TCreateInfo& createInfo)
{
  DXGI_MODE_DESC bufferDesc{};
  bufferDesc.Width                   = createInfo.m_width;
  bufferDesc.Height                  = createInfo.m_height;
  bufferDesc.RefreshRate.Denominator = 1;
  bufferDesc.RefreshRate.Numerator   = 60;
  bufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
  bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

  DXGI_SWAP_CHAIN_DESC swapChainDesc{};
  swapChainDesc.BufferDesc         = bufferDesc;
  swapChainDesc.SampleDesc.Count   = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.BufferCount        = 1;
  swapChainDesc.OutputWindow       = createInfo.m_hwnd;
  swapChainDesc.Windowed           = !createInfo.m_fullscreen;
  swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;

  HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                             D3D_DRIVER_TYPE_HARDWARE,
                                             nullptr,
                                             0,
                                             nullptr,
                                             0,
                                             D3D11_SDK_VERSION,
                                             &swapChainDesc,
                                             &m_pSwapChain.Get(),
                                             &m_pDevice.Get(),
                                             nullptr,
                                             &m_pDeviceContext.Get());

  CGE_HRESULT_CHECK(hr, "can't create device and swapchain");

  return TResult::Okay();
}
}
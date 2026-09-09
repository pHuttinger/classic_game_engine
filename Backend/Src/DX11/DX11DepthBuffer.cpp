//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11DepthBuffer.h"

namespace cge::rhi::dx11
{
CDepthBuffer::CDepthBuffer(IInstance& instance)
  : m_instance(dynamic_cast<CInstance&>(instance))
{
}

TResult CDepthBuffer::Initialize(const TDepthBufferCreateInfo& createInfo)
{
  CGE_TRY(CreateDepthStencilView(createInfo));
  return TResult::Okay();
}

TResult CDepthBuffer::CreateDepthStencilView(const TDepthBufferCreateInfo& createInfo)
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
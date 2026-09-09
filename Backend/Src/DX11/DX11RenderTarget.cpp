//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11RenderTarget.h"

namespace cge::rhi::dx11
{
CRenderTarget::CRenderTarget(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CRenderTarget::Initialize(const TRenderTargetCreateInfo& createInfo)
{
  CGE_TRY(CreateRenderTargetView(createInfo));
  return TResult::Okay();
}

void CRenderTarget::Clear()
{
  m_instance.GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
}

TResult CRenderTarget::CreateRenderTargetView(const TRenderTargetCreateInfo& createInfo)
{
  D3D11_TEXTURE2D_DESC textureDesc{};
  textureDesc.Width          = createInfo.m_width;
  textureDesc.Height         = createInfo.m_height;
  textureDesc.MipLevels      = 1;
  textureDesc.ArraySize      = 1;
  textureDesc.Format         = DXGI_FORMAT_R8G8B8A8_UNORM;
  textureDesc.SampleDesc     = { 1, 0 };
  textureDesc.Usage          = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags      = 0;

  HRESULT hr = m_instance.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_pTexture.Get());
  CGE_HRESULT_CHECK(hr, "Can't create Texture2D");

  hr = m_instance.GetDevice()->CreateRenderTargetView(m_pTexture.Get(), nullptr, &m_pRenderTargetView.Get());
  CGE_HRESULT_CHECK(hr, "Can't create RenderTargetView");

  return TResult::Okay();
}
}
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
  CGE_TRY(CreateTexture2D(createInfo));
  CGE_TRY(CreateRenderTargetView());
  CGE_TRY(CreateShaderResourceView());
  return TResult::Okay();
}

void CRenderTarget::Clear(const glm::vec4& color)
{
  m_instance.GetDeviceContext()->ClearRenderTargetView(m_pRenderTargetView.Get(), D3DXCOLOR(color.r, color.g, color.b, color.a));
}

TResult CRenderTarget::CreateTexture2D(const TRenderTargetCreateInfo& createInfo)
{
  D3D11_TEXTURE2D_DESC textureDesc{};
  textureDesc.Width          = createInfo.m_width;
  textureDesc.Height         = createInfo.m_height;
  textureDesc.MipLevels      = 1;
  textureDesc.ArraySize      = 1;
  textureDesc.Format         = CGE_DEFAULT_DXGI_FORMAT;
  textureDesc.SampleDesc     = { 1, 0 };
  textureDesc.Usage          = D3D11_USAGE_DEFAULT;
  textureDesc.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags      = 0;

  HRESULT hr = m_instance.GetDevice()->CreateTexture2D(&textureDesc, nullptr, &m_pTexture.Get());
  CGE_HRESULT_CHECK(hr, "Can't create Texture2D");

  return TResult::Okay();
}

TResult CRenderTarget::CreateRenderTargetView()
{
  HRESULT hr = m_instance.GetDevice()->CreateRenderTargetView(m_pTexture.Get(), nullptr, &m_pRenderTargetView.Get());
  CGE_HRESULT_CHECK(hr, "Can't create RenderTargetView");

  return TResult::Okay();
}

TResult CRenderTarget::CreateShaderResourceView()
{
  D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc{};
  shaderResourceViewDesc.Format                    = CGE_DEFAULT_DXGI_FORMAT;
  shaderResourceViewDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
  shaderResourceViewDesc.Texture2D.MipLevels       = 1;
  shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

  HRESULT hr = m_instance.GetDevice()->CreateShaderResourceView(m_pTexture.Get(), &shaderResourceViewDesc, &m_pShaderResourceView.Get());
  CGE_HRESULT_CHECK(hr, "Can't create ShaderResourceView");

  return TResult::Okay();
}
}
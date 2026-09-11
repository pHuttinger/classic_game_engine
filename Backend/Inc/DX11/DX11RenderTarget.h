//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../RenderTarget.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CRenderTarget final : public IRenderTarget 
{
public:

  CRenderTarget(IInstance& instance);

  TResult Initialize(const TRenderTargetCreateInfo& createInfo) override;

  void Clear() override;

  ID3D11RenderTargetView* GetRenderTargetView() { return m_pRenderTargetView.Get(); }
  ID3D11ShaderResourceView* GetShaderResourceView() { return m_pShaderResourceView.Get(); }

private:

  TResult CreateTexture2D(const TRenderTargetCreateInfo& createInfo);
  TResult CreateRenderTargetView();
  TResult CreateShaderResourceView();

  CInstance& m_instance;

  CComPtr<ID3D11Texture2D>          m_pTexture;
  CComPtr<ID3D11RenderTargetView>   m_pRenderTargetView;
  CComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
};
}
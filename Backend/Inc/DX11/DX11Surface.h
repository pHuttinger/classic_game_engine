//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/ComPtr.h>
#include "../Surface.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CSurface : public ISurface
{
public:

  CSurface(IInstance& instance);

  TResult Initialize(const TSurfaceCreateInfo& createInfo) override;
  
  void Clear() override;

private:

  TResult InitializeRenderTargetView(const TSurfaceCreateInfo& createInfo);
  TResult InitializeDepthBuffer(const TSurfaceCreateInfo& createInfo);

  CInstance& m_instance;

  CComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
  CComPtr<ID3D11Texture2D>        m_pDepthBuffer;
  CComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../DepthBuffer.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CDepthBuffer final : public IDepthBuffer
{
public:

  CDepthBuffer(IInstance& instance);

  TResult Initialize(const TDepthBufferCreateInfo& createInfo) override;

  ID3D11DepthStencilView* GetDepthStencilView() { return m_pDepthStencilView.Get(); }

private:

  TResult CreateDepthStencilView(const TDepthBufferCreateInfo& createInfo);

  CInstance& m_instance;

  CComPtr<ID3D11Texture2D>        m_pDepthBuffer;
  CComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/ComPtr.h>
#include "DX11.h"
#include "../Instance.h"

namespace cge::rhi::dx11
{
class CInstance final : public IInstance
{
public:

  CInstance() = default;
  ~CInstance();

  TResult Create(const TCreateInfo& createInfo);

  std::unique_ptr<IPipeline> CreatePipeline() override;

  IDXGISwapChain* GetSwapChain() { return m_pSwapChain.Get(); }

private:

  CComPtr<IDXGISwapChain>      m_pSwapChain;
  CComPtr<ID3D11Device>        m_pDevice;
  CComPtr<ID3D11DeviceContext> m_pDeviceContext;
};
}
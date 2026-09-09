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

  TSurfaceCreateInfo GetCreateInfo() const override { return m_createInfo; }

private:

  TResult InitializeRenderTargetView(const TSurfaceCreateInfo& createInfo);

  CInstance&                      m_instance;
  TSurfaceCreateInfo              m_createInfo;
  CComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
};
}
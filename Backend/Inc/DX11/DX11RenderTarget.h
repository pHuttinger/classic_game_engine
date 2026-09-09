//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/ComPtr.h>
#include "../RenderTarget.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CRenderTarget : public IRenderTarget 
{
public:

  CRenderTarget(IInstance& instance);

  TResult Initialize(const TRenderTargetCreateInfo& createInfo) override;

  void Clear() override;

private:

  TResult CreateRenderTargetView(const TRenderTargetCreateInfo& createInfo);

  CInstance& m_instance;

  CComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
};
}
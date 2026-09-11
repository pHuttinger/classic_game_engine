//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../PixelShader.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CPixelShader final : public IPixelShader
{
public:

  CPixelShader(IInstance& instance);

  TResult Initialize(const TPixelShaderCreateInfo& createInfo) override;

private:

  CInstance& m_instance;

  CComPtr<ID3D11PixelShader> m_pPixelShader;
};
}
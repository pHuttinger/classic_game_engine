//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Texture.h"
#include "../DX11/DX11Instance.h"

namespace cge::rhi::dx11
{
class CTexture final : public ITexture
{
public:

  CTexture(IInstance& instance);

  TResult Initialize(const TTextureCreateInfo& createInfo) override;

  ID3D11ShaderResourceView* GetShaderResourceView() { return m_pShaderResourceView.Get(); }

private:

  CInstance& m_instance;

  CComPtr<ID3D11ShaderResourceView> m_pShaderResourceView;
};
}
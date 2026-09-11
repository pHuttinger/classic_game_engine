//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../VertexShader.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CVertexShader final : public IVertexShader
{
public:

  CVertexShader(IInstance& instance);

  TResult Initialize(const TVertexShaderCreateInfo& createInfo) override;

private:

  CInstance& m_instance;

  CComPtr<ID3D11VertexShader> m_pVertexShader;
};
}
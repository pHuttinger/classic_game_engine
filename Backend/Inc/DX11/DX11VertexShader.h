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

  std::vector<char>& GetBytecode() { return m_bytecode; }

private:

  CInstance& m_instance;

  CComPtr<ID3D11VertexShader> m_pVertexShader;
  std::vector<char>           m_bytecode;
};
}
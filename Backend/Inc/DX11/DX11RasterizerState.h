//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../RasterizerState.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CRasterizerState final : public IRasterizerState
{
public:

  CRasterizerState(IInstance& instance);

  TResult Initialize(const TRasterizerStateCreateInfo& createInfo) override;

  ID3D11RasterizerState* GetRasterizerState() { return m_pRasterizerState.Get(); }

private:

  D3D11_FILL_MODE GetFillMode  (const EFillMode fillMode  ) const;
  D3D11_CULL_MODE GetCullMode  (const ECullMode cullMode  ) const;
  bool            GetFrontFace (const EFrontFace frontFace) const;

  CInstance& m_instance;

  CComPtr<ID3D11RasterizerState> m_pRasterizerState;
};
}
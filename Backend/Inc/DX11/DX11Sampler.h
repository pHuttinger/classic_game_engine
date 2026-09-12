//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Sampler.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CSampler final : public ISampler
{
public:

  CSampler(IInstance& instance);

  TResult Initialize() override;

private:

  CInstance& m_instance;

  CComPtr<ID3D11SamplerState> m_pSamplerState;
};
}
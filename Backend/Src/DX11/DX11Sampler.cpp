//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Sampler.h"

namespace cge::rhi::dx11
{
CSampler::CSampler(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CSampler::Initialize()
{
  D3D11_SAMPLER_DESC sampDesc{};
  sampDesc.Filter         = D3D11_FILTER_ANISOTROPIC;
  sampDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.MaxAnisotropy  = 16;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  sampDesc.MinLOD         = 0;
  sampDesc.MaxLOD         = D3D11_FLOAT32_MAX;

  HRESULT hr = m_instance.GetDevice()->CreateSamplerState(&sampDesc, &m_pSamplerState.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create SamplerState");

  return TResult::Okay();
}
}
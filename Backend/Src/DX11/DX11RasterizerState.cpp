//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11RasterizerState.h"

namespace cge::rhi::dx11
{
CRasterizerState::CRasterizerState(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CRasterizerState::Initialize(const TRasterizerStateCreateInfo& createInfo)
{
  D3D11_RASTERIZER_DESC rasterDesc = {};

  rasterDesc.FillMode              = GetFillMode(createInfo.m_fillMode);
  rasterDesc.CullMode              = GetCullMode(createInfo.m_cullMode);
  rasterDesc.FrontCounterClockwise = GetFrontFace(createInfo.m_frontFace);
  rasterDesc.DepthClipEnable       = true;
  rasterDesc.ScissorEnable         = false;
  rasterDesc.MultisampleEnable     = true;
  rasterDesc.AntialiasedLineEnable = true;

  auto*& pRasterizerState = m_pRasterizerState.Get();
  HRESULT hr = m_instance.GetDevice()->CreateRasterizerState(&rasterDesc, &pRasterizerState);
  CGE_HRESULT_CHECK(hr, "Failed to initialize RasterizerState");

  return TResult::Okay();
}

D3D11_FILL_MODE CRasterizerState::GetFillMode(const EFillMode fillMode) const
{
  switch (fillMode)
  {
    case EFillMode::Solid    : return D3D11_FILL_SOLID;
    case EFillMode::Wireframe: return D3D11_FILL_WIREFRAME;
  }

  return D3D11_FILL_SOLID;
}

D3D11_CULL_MODE CRasterizerState::GetCullMode(const ECullMode cullMode) const
{
  switch (cullMode)
  {
    case ECullMode::None : return D3D11_CULL_NONE;
    case ECullMode::Front: return D3D11_CULL_FRONT;
    case ECullMode::Back : return D3D11_CULL_BACK;
  }

  return D3D11_CULL_NONE;
}

bool CRasterizerState::GetFrontFace(const EFrontFace frontFace) const
{
  //needs to be inverted because rendering is RightHanded!
  return frontFace != EFrontFace::CounterClockwise;
}
}
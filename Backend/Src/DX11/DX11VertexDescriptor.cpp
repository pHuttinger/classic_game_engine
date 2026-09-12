//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11VertexDescriptor.h"
#include "../../Inc/DX11/DX11VertexShader.h"

namespace cge::rhi::dx11
{
CVertexDescriptor::CVertexDescriptor(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CVertexDescriptor::Initialize(const TVertexDescriptorCreateInfo& createInfo)
{
  std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc =
  {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
  };

  CVertexShader* vertexShader = static_cast<CVertexShader*>(createInfo.pVertexShader);
  std::vector<char> vsBytecode = vertexShader->GetBytecode();

  HRESULT hr = m_instance.GetDevice()->CreateInputLayout(layoutDesc.data(), layoutDesc.size(), vsBytecode.data(), vsBytecode.size(), &m_pInputLayout.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create VertexDescriptor");

  return TResult::Okay();
}
}

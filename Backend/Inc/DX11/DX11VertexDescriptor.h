//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../VertexDescriptor.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CVertexDescriptor final : public IVertexDescriptor
{
public:

  CVertexDescriptor(IInstance& instance);

  TResult Initialize(const TVertexDescriptorCreateInfo& createInfo) override;

  ID3D11InputLayout* GetInputLayout() { return m_pInputLayout.Get(); }

private:

  const char* GetInputLayoutSemanticName(EVertexAttributeUsage usage) const;
  DXGI_FORMAT GetDxgiFormat(EVertexAttributeFormat format) const;
  size_t GetFormatSize(EVertexAttributeFormat format) const;
  std::vector<D3D11_INPUT_ELEMENT_DESC> CreateInputLayoutDesc(const std::vector<TVertexAttribute>& vertexAttributeInfos) const;

  CInstance& m_instance;

  CComPtr<ID3D11InputLayout> m_pInputLayout;
};
}
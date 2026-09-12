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

  CInstance& m_instance;

  CComPtr<ID3D11InputLayout> m_pInputLayout;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Buffer.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CBuffer final : public IBuffer
{
public:

  CBuffer(IInstance& instance);

  TResult Initialize(const TBufferCreateInfo& createInfo);

private:

  D3D11_USAGE GetDX11Usage(const EBufferUsage bufferUsage) const;
  D3D11_BIND_FLAG GetDX11BindFlag(const EBufferType bufferType) const;

  CInstance& m_instance;

  CComPtr<ID3D11Buffer> m_pBuffer;
};
}
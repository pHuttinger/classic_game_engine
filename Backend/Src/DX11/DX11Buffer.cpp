//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Buffer.h"

namespace cge::rhi::dx11
{
CBuffer::CBuffer(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CBuffer::Initialize(const TBufferCreateInfo& createInfo)
{
  m_createInfo = createInfo;

  D3D11_BUFFER_DESC bufferDesc{};
  bufferDesc.Usage          = GetDX11Usage(createInfo.m_usage);
  bufferDesc.BindFlags      = GetDX11BindFlag(createInfo.m_bufferType);
  bufferDesc.ByteWidth      = createInfo.m_size;
  bufferDesc.CPUAccessFlags = 0;
  bufferDesc.MiscFlags      = 0;

  HRESULT hr = S_OK;
  if (createInfo.m_pData == nullptr)
  {
    hr = m_instance.GetDevice()->CreateBuffer(&bufferDesc, nullptr, &m_pBuffer.Get());
  }
  else
  {
    D3D11_SUBRESOURCE_DATA subresourceData{};
    subresourceData.pSysMem = createInfo.m_pData;
    hr = m_instance.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &m_pBuffer.Get());
  }

  CGE_HRESULT_CHECK(hr, "Failed to initialize Buffer");

  return TResult::Okay();
}

D3D11_USAGE CBuffer::GetDX11Usage(const EBufferUsage bufferUsage) const
{
  switch (bufferUsage)
  {
    case EBufferUsage::Default: return D3D11_USAGE_DEFAULT;
    case EBufferUsage::Dynamic: return D3D11_USAGE_DYNAMIC;
  }
}

D3D11_BIND_FLAG CBuffer::GetDX11BindFlag(const EBufferType bufferType) const
{
  switch (bufferType)
  {
    case EBufferType::VertexBuffer  : return D3D11_BIND_VERTEX_BUFFER;
    case EBufferType::IndexBuffer   : return D3D11_BIND_INDEX_BUFFER;
    case EBufferType::ConstantBuffer: return D3D11_BIND_CONSTANT_BUFFER;
  }
}
}
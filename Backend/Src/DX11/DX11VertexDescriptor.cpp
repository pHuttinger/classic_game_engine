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
  std::vector<D3D11_INPUT_ELEMENT_DESC> layoutDesc = CreateInputLayoutDesc(createInfo.m_vertexAttributeInfos);

  CVertexShader* vertexShader = static_cast<CVertexShader*>(createInfo.m_pVertexShader);
  std::vector<char> vsBytecode = vertexShader->GetBytecode();

  HRESULT hr = m_instance.GetDevice()->CreateInputLayout(layoutDesc.data(), layoutDesc.size(), vsBytecode.data(), vsBytecode.size(), &m_pInputLayout.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create VertexDescriptor");

  return TResult::Okay();
}

const char* CVertexDescriptor::GetInputLayoutSemanticName(EVertexAttributeUsage usage) const
{
  switch (usage)
  {
    case EVertexAttributeUsage::Position: return "POSITION";
    case EVertexAttributeUsage::Texcoord: return "TEXCOORD";
  }
}

DXGI_FORMAT CVertexDescriptor::GetDxgiFormat(EVertexAttributeFormat format) const
{
  switch (format)
  {
    case EVertexAttributeFormat::Float2: return DXGI_FORMAT_R32G32_FLOAT;
    case EVertexAttributeFormat::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
  }
}

size_t CVertexDescriptor::GetFormatSize(EVertexAttributeFormat format) const
{
  switch (format)
  {
    case EVertexAttributeFormat::Float2: return sizeof(glm::vec2);
    case EVertexAttributeFormat::Float3: return sizeof(glm::vec3);
  }
}

std::vector<D3D11_INPUT_ELEMENT_DESC> CVertexDescriptor::CreateInputLayoutDesc(const std::vector<TVertexAttribute>& vertexAttributeInfos) const
{
  std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

  size_t offset = 0U;
  for (auto& info : vertexAttributeInfos)
  {
    D3D11_INPUT_ELEMENT_DESC element {
      GetInputLayoutSemanticName(info.m_usage),
      0U,
      GetDxgiFormat(info.m_format),
      0U,
      offset,
      D3D11_INPUT_PER_VERTEX_DATA,
      0U };

    inputLayoutDesc.push_back(element);
    offset += GetFormatSize(info.m_format);
  }

  return inputLayoutDesc;
}
}

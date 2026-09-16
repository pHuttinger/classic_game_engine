//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11VertexShader.h"
#include <Common/Inc/FileSystem/BinaryFileReader.h>

namespace cge::rhi::dx11
{
CVertexShader::CVertexShader(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CVertexShader::Initialize(const TVertexShaderCreateInfo& createInfo)
{
  filesystem::CBinaryFileReader binaryFileReader;

  CGE_TRY(binaryFileReader.Read(m_instance.GetShaderFilename(createInfo.m_shaderName), m_bytecode));

  HRESULT hr = m_instance.GetDevice()->CreateVertexShader(m_bytecode.data(), m_bytecode.size(), nullptr, &m_pVertexShader.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create VertexShader");

  return TResult::Okay();
}
}
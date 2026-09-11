//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11PixelShader.h"
#include <Common/Inc/FileSystem/BinaryFileReader.h>

namespace cge::rhi::dx11
{
CPixelShader::CPixelShader(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CPixelShader::Initialize(const TPixelShaderCreateInfo& createInfo)
{
  filesystem::CBinaryFileReader binaryFileReader;

  std::vector<char> bytecode;
  CGE_TRY(binaryFileReader.Read(createInfo.m_filename, bytecode));

  HRESULT hr = m_instance.GetDevice()->CreatePixelShader(bytecode.data(), bytecode.size(), nullptr, &m_pPixelShader.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create PixelShader");

  return TResult::Okay();
}
}
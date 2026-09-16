//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//------------------------------------------------
// TPixelShaderCreateInfo
//------------------------------------------------
struct TPixelShaderCreateInfo final
{
  std::string m_shaderName;
};

//------------------------------------------------
// IPixelShader
//------------------------------------------------
class IPixelShader
{
public:

  virtual ~IPixelShader() = default;

  virtual TResult Initialize(const TPixelShaderCreateInfo& createInfo) = 0;
};
}
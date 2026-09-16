//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//------------------------------------------------
// TVertexShaderCreateInfo
//------------------------------------------------
struct TVertexShaderCreateInfo final
{
  std::string m_shaderName;
};

//------------------------------------------------
// IVertexShader
//------------------------------------------------
class IVertexShader
{
public:

  virtual ~IVertexShader() = default;

  virtual TResult Initialize(const TVertexShaderCreateInfo& createInfo) = 0;
};
}
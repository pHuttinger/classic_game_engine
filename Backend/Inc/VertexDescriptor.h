//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
#include "VertexShader.h"

namespace cge::rhi
{
//----------------------------------------------------
// TVertexDescriptorCreateInfo
//----------------------------------------------------
struct TVertexDescriptorCreateInfo final
{
  IVertexShader* m_pVertexShader = nullptr;
  std::vector<TVertexAttribute> m_vertexAttributeInfos;
};

//----------------------------------------------------
// IVertexDescriptor
//----------------------------------------------------
class IVertexDescriptor
{
public:

  virtual ~IVertexDescriptor() = default;

  virtual TResult Initialize(const TVertexDescriptorCreateInfo& createInfo) = 0;
};
}
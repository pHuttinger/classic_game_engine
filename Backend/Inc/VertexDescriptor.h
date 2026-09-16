//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
#include "VertexShader.h"

namespace cge::rhi
{
//---------------------------------------------------
// EVertexAttributeUsage
//---------------------------------------------------
enum class EVertexAttributeUsage
{
  Position,
  Texcoord,
};

//---------------------------------------------------
// EVertexAttributeFormat
//---------------------------------------------------
enum class EVertexAttributeFormat
{
  Float2 = 1,
  Float3 = 2,
};

//---------------------------------------------------
// TVertexAttribute
//---------------------------------------------------
struct TVertexAttribute final
{
  EVertexAttributeUsage m_usage   = EVertexAttributeUsage::Position;
  EVertexAttributeFormat m_format = EVertexAttributeFormat::Float2;
};

//----------------------------------------------------
// TVertexDescriptorCreateInfo
//----------------------------------------------------
struct TVertexDescriptorCreateInfo final
{
  IVertexShader* m_pVertexShader = nullptr;
  std::vector<TVertexAttribute> m_vertexAttributeInfos;
};

//----------------------------------------------------
// TBufferCreateInfo
//----------------------------------------------------
class IVertexDescriptor
{
public:

  virtual ~IVertexDescriptor() = default;

  virtual TResult Initialize(const TVertexDescriptorCreateInfo& createInfo) = 0;
};
}
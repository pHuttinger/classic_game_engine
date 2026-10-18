//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

namespace cge
{
//---------------------------------------------------
// EVertexAttributeUsage
//---------------------------------------------------
enum class EVertexAttributeUsage
{
  Position,
  Texcoord,
  Normal,
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
  EVertexAttributeUsage  m_usage  = EVertexAttributeUsage::Position;
  EVertexAttributeFormat m_format = EVertexAttributeFormat::Float2;
};
}
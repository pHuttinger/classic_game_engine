//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//------------------------------------------------
// EFillMode
//------------------------------------------------
enum class EFillMode
{
  Solid,
  Wireframe,
};

//------------------------------------------------
// ECullMode
//------------------------------------------------
enum class ECullMode
{
  None,
  Back,
  Front,
};

//------------------------------------------------
// EFrontFace
//------------------------------------------------
enum class EFrontFace
{
  Clockwise,
  CounterClockwise
};

//------------------------------------------------
// TRasterizerStateCreateInfo
//------------------------------------------------
struct TRasterizerStateCreateInfo final
{
  EFillMode  m_fillMode  = EFillMode::Solid;
  ECullMode  m_cullMode  = ECullMode::None;
  EFrontFace m_frontFace = EFrontFace::CounterClockwise;
};

//------------------------------------------------
// IRasterizerState
//------------------------------------------------
class IRasterizerState
{
public:

  virtual ~IRasterizerState() = default;

  virtual TResult Initialize(const TRasterizerStateCreateInfo& createInfo) = 0;
};
}
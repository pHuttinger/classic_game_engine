//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
#include "Pipeline.h"

namespace cge::rhi
{
//----------------------------------------------------
// EBackend
//----------------------------------------------------
enum class EBackend
{
  Undefined,
  DX11,
  OpenGL,
};

//----------------------------------------------------
// TCreateInfo
//----------------------------------------------------
struct TCreateInfo final
{
  EBackend  m_backend    = EBackend::Undefined;
  HWND      m_hwnd       = nullptr;
  HINSTANCE m_hinstance  = nullptr;
  bool      m_fullscreen = false;
  uint16_t  m_width      = 800U;
  uint16_t  m_height     = 600U;
};

//----------------------------------------------------
// IInstance
//----------------------------------------------------
class IInstance
{
public:

  virtual ~IInstance() = default;

  virtual std::unique_ptr<IPipeline> CreatePipeline() = 0;
};

//----------------------------------------------------
// CreateInstance - Function
//----------------------------------------------------
TResult CreateInstance(const TCreateInfo& createInfo, std::unique_ptr<IInstance>& pInstance);
}
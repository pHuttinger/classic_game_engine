//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
#include "Pipeline.h"
#include "Surface.h"
#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

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

  virtual TResult CreateSurface(const TSurfaceCreateInfo& createInfo, std::unique_ptr<ISurface>& pSurface) = 0;
  virtual TResult CreateRenderTarget(const TRenderTargetCreateInfo& createInfo, std::unique_ptr<IRenderTarget>& pRenderTarget) = 0;
  virtual TResult CreateDepthBuffer(const TDepthBufferCreateInfo& createInfo, std::unique_ptr<IDepthBuffer>& pDepthBuffer) = 0;
  virtual TResult CreatePixelShader(const TPixelShaderCreateInfo& createInfo, std::unique_ptr<IPixelShader>& pPixelShader) = 0;
  virtual TResult CreateVertexShader(const TVertexShaderCreateInfo& createInfo, std::unique_ptr<IVertexShader>& pVertexShader) = 0; 
};

//----------------------------------------------------
// CreateInstance - Function
//----------------------------------------------------
TResult CreateInstance(const TCreateInfo& createInfo, std::unique_ptr<IInstance>& pInstance);
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
//#include "Device.h"
//#include "Swapchain.h"
//#include "RenderTarget.h"

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

////----------------------------------------------------
//// TCreateInfo
////----------------------------------------------------
//struct TCreateInfo final
//{
//  HWND      m_hwnd      = nullptr;
//  HINSTANCE m_hinstance = nullptr;
//};

//----------------------------------------------------
// IInstance
//----------------------------------------------------
class BACKEND_API IInstance
{
public:

  virtual ~IInstance() = default;

  //virtual EResult CreateDevice(std::unique_ptr<IDevice>& pDevice) const = 0;
  //virtual EResult CreateSwapchain(const IDevice& device, std::unique_ptr<ISwapchain>& pSwapchain) const = 0;
  //virtual EResult CreateRenderTarget(const IDevice& device, ISwapchain& swapchain, std::unique_ptr<IRenderTarget>& pRenderTarget) const = 0;
};

//----------------------------------------------------
// CreateInstance - Function
//----------------------------------------------------
TResult BACKEND_API CreateInstance(const EBackend backend, std::unique_ptr<IInstance>& pInstance);
}
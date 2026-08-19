//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>

namespace cge::render
{
//----------------------------------------------------
// TBackendCreateInfo
//----------------------------------------------------
struct TBackendCreateInfo final
{
  HWND          m_hwnd      = nullptr;
  HINSTANCE     m_hinstance = nullptr;
  rhi::EBackend m_backend   = rhi::EBackend::Undefined;
};

//----------------------------------------------------
// CBackend
//----------------------------------------------------
class CBackend final
{
public:

  CBackend() = default;
  ~CBackend();

  TResult Initialize(const TBackendCreateInfo& createInfo);

  rhi::IInstance& GetInstance() const { return *m_pInstance.get(); }
  //rhi::IDevice& GetDevice() const { return *m_pDevice.get(); }
  //rhi::ISwapchain& GetSwapchain() const { return *m_pSwapchain.get(); }
  //rhi::IRenderTarget& GetRenderTarget() const { return *m_pRenderTarget.get(); }

private:

  std::unique_ptr<rhi::IInstance> m_pInstance;
  //std::unique_ptr<rhi::IDevice> m_pDevice;
  //std::unique_ptr<rhi::ISwapchain> m_pSwapchain;
  //std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget;
};
}

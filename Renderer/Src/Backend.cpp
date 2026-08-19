//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Backend.h"

namespace cge::render
{
CBackend::~CBackend()
{
  CGE_WARN("cleanup backend...");
}

TResult CBackend::Initialize(const TBackendCreateInfo& createInfo)
{
  CGE_TRY(rhi::CreateInstance(createInfo.m_backend, m_pInstance));
  //CGE_TRY(m_pInstance->CreateDevice(m_pDevice));
  //CGE_TRY(m_pInstance->CreateSwapchain(*m_pDevice.get(), m_pSwapchain));
  //CGE_TRY(m_pInstance->CreateRenderTarget(*m_pDevice.get(), *m_pSwapchain.get(), m_pRenderTarget));

  return TResult::Okay();
}
}
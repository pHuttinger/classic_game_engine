/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../Inc/Instance.h"

namespace cge
{
//---------------------------------------------------
// CGameLoop
//---------------------------------------------------
CGameLoop::CGameLoop(CInstance& app)
  : m_app(app)
{
}

void CGameLoop::OnTick()
{
  m_app.OnTick();
}

//---------------------------------------------------
// CInstance
//---------------------------------------------------
CInstance::CInstance()
  : m_gameLoop(*this)
  , m_window(m_gameLoop)
  //, m_assetManager(m_renderProxy)
{
}

TResult CInstance::Create(TInstanceCreateInfo& createInfo)
{
  CGE_INIT();

  CGE_TRY(m_window.Create(createInfo.m_windowCreateInfo));
  CGE_MILESTONE("window created...");

  CGE_TRY(CreateRenderProxy(createInfo));
  CGE_MILESTONE("renderProxy created...");

  m_pGame = std::move(createInfo.m_pGame);
  CGE_TRY(m_pGame->OnCreate(*this));
  CGE_MILESTONE("game created...");

  return TResult::Okay();
}

void CInstance::Run()
{
  CGE_INFO("start gameloop...");
  m_window.Show();
  m_window.StartLoop();
}

TResult CInstance::CreateRenderProxy(const TInstanceCreateInfo& createInfo)
{
  const TWindowData& windowData = m_window.GetWindowData();

  rhi::TCreateInfo backendCreateInfo
  {
    .m_backend   = createInfo.m_backend,
    .m_hwnd      = windowData.m_hwnd,
    .m_hinstance = windowData.m_hinstance,
  };

  CGE_TRY(m_renderProxy.Initialize(backendCreateInfo));

  return TResult::Okay();
}

void CInstance::OnTick()
{
  m_timer.Update();
  m_renderProxy.Open();
  //m_world.EvaluateScene(m_renderProxy);
  m_renderProxy.Present();
  m_pGame->OnTick(m_timer.GetDeltaTime());
}
}
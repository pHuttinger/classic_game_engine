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

  TResult result = m_window.Create(createInfo.m_windowCreateInfo);
  CGE_CHECK(result);
  CGE_MILESTONE("window created...");

  result = CreateRenderProxy(createInfo);
  CGE_CHECK(result);
  CGE_MILESTONE("renderProxy created...");

  m_pGame = std::move(createInfo.m_pGame);
  result = m_pGame->OnCreate(*this);
  CGE_CHECK(result);
  CGE_MILESTONE("game created...");

  return TResult::Okay();
}

void CInstance::Start()
{
  CGE_INFO("start gameloop...");
  m_window.Show();
  m_window.StartLoop();
}

TResult CInstance::CreateRenderProxy(const TInstanceCreateInfo& createInfo)
{
 /* const TWindowData& windowData = m_window.GetWindowData();

  rendering::TBackendCreateInfo backendCreateInfo
  {
    .m_hwnd      = windowData.m_hwnd,
    .m_hinstance = windowData.m_hinstance,
    .m_backend   = createInfo.m_backend,
  };

  TResult result = m_renderProxy.Initialize(backendCreateInfo);
  CGE_CHECK(result);*/

  return TResult::Okay();
}

void CInstance::OnTick()
{
  //m_timer.Update();

  //m_renderProxy.Open();

  //m_world.EvaluateScene(m_renderProxy);

  //m_renderProxy.Present();

  //m_pGame->OnTick(m_timer.GetDeltaTime());
}
}
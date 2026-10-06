//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Window.h>
#include <Common/Inc/Timer.h>
#include "RenderProxy.h"
#include "SceneManager.h"
#include "AssetManager.h"

namespace cge
{
class CInstance;

//---------------------------------------------------
// IGame
//---------------------------------------------------
class IGame
{
public:

  virtual ~IGame() = default;

  virtual TResult OnCreate(CInstance& instance) = 0;
  virtual void OnTick(const float deltaTime) = 0;
};

//---------------------------------------------------
// TInstanceCreateInfo
//---------------------------------------------------
struct TInstanceCreateInfo final
{
  TWindowCreateInfo      m_windowCreateInfo;
  rhi::EBackend          m_backend = rhi::EBackend::DX11;
  std::unique_ptr<IGame> m_pGame;
};

//---------------------------------------------------
// CGameLoop
//---------------------------------------------------
class CGameLoop final : public IWindowLoopCallback
{
public:

  CGameLoop(CInstance& app);

  void OnTick() override;

private:

  CInstance& m_app;
};

//---------------------------------------------------
// CInstance
//---------------------------------------------------
class CInstance final
{
friend class CGameLoop;

public:

  CInstance();
  ~CInstance() = default;

  TResult Create(TInstanceCreateInfo& createInfo);
  void Run();

  CSceneManager& GetSceneManager() { return m_sceneManager; }
  CAssetManager& GetAssetManager() { return m_assetManager; }

private:

  TResult CreateRenderProxy(const TInstanceCreateInfo& createInfo);
  void OnTick();

  CWindow                m_window;
  CTimer                 m_timer;
  CGameLoop              m_gameLoop;
  CRenderProxy           m_renderProxy;
  CSceneManager          m_sceneManager;
  CAssetManager          m_assetManager;
  std::unique_ptr<IGame> m_pGame;
};
}
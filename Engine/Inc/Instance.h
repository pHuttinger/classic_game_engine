//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "App/Window.h"
//#include "RenderProxy.h"
//#include "Timer.h"
//#include "AssetManager.h"
//#include "../Scene/World.h"

namespace cge
{
class CInstance;

//---------------------------------------------------
// IGame
//---------------------------------------------------
class ENGINE_API IGame
{
public:

  virtual ~IGame() = default;

  virtual TResult OnCreate(CInstance& instance) = 0;
  virtual void OnTick(const float deltaTime) = 0;
};

//---------------------------------------------------
// TInstanceCreateInfo
//---------------------------------------------------
struct ENGINE_API TInstanceCreateInfo final
{
  TWindowCreateInfo m_windowCreateInfo;
  //rhi::EBackend m_backend;
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
class ENGINE_API CInstance final
{
  friend class CGameLoop;

public:

  CInstance();
  ~CInstance() = default;

  TResult Create(TInstanceCreateInfo& createInfo);
  void Start();

  //CWorld& GetWorld() { return m_world; }
  //CAssetManager& GetAssetManager() { return m_assetManager; }

private:

  TResult CreateRenderProxy(const TInstanceCreateInfo& createInfo);
  void OnTick();

  CWindow m_window;
  CGameLoop m_gameLoop;
 /* CRenderProxy m_renderProxy;
  CTimer m_timer;
  CWorld m_world;
  CAssetManager m_assetManager;*/
  std::unique_ptr<IGame> m_pGame;
};
}
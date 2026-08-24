//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge
{
//---------------------------------------------------
// TWindowCreateInfo
//---------------------------------------------------
struct TWindowCreateInfo final
{
  std::string m_title      = "classic game engine";
  uint16_t    m_width      = 1024U;
  uint16_t    m_height     = 720U;
  bool        m_fullscreen = false;
};

//---------------------------------------------------
// TWindowData
//---------------------------------------------------
struct TWindowData final
{
  HWND      m_hwnd      = nullptr;
  HINSTANCE m_hinstance = nullptr;
};

//---------------------------------------------------
// IWindowLoopCallback
//---------------------------------------------------
class IWindowLoopCallback
{
public:

  virtual ~IWindowLoopCallback() = default;

  virtual void OnTick() = 0;
};

//---------------------------------------------------
// CWindow
//---------------------------------------------------
class CWindow final
{
public:

  CWindow(IWindowLoopCallback& windowLoopCallback);
  ~CWindow();

  TResult Create(const TWindowCreateInfo& windowCreateInfo);
  void Show() const;
  void StartLoop();

  const TWindowData& GetWindowData() { return m_windowData; }

private:

  static void ExitApplication();
  static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

  TWindowData m_windowData;
  IWindowLoopCallback& m_windowLoopCallback;
};
}
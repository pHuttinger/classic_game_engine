//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/App/Window.h"

namespace cge
{
CWindow::CWindow(IWindowLoopCallback& windowLoopCallback)
  : m_windowLoopCallback(windowLoopCallback)
{
}

CWindow::~CWindow()
{
  CGE_WARN("exit application...");
}

TResult CWindow::Create(const TWindowCreateInfo& windowCreateInfo)
{
  m_windowData.m_hinstance = GetModuleHandle(nullptr);

  LPCTSTR wndClassName = TEXT("cge_window_class");
  WNDCLASSEX wc{};

  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = WndProc;
  wc.cbClsExtra    = 0L;
  wc.cbWndExtra    = 0L;
  wc.hInstance     = m_windowData.m_hinstance;
  wc.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);
  wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName  = nullptr;
  wc.lpszClassName = wndClassName;
  wc.hIconSm       = LoadIcon(nullptr, IDI_WINLOGO);

  if (!RegisterClassEx(&wc))
    return TResult::Error("can't create window class");

  m_windowData.m_hwnd = CreateWindowEx(
    0L,
    wndClassName,
    TEXT(windowCreateInfo.m_title.c_str()),
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    windowCreateInfo.m_width,
    windowCreateInfo.m_height,
    nullptr,
    nullptr,
    m_windowData.m_hinstance,
    nullptr
  );

  if (m_windowData.m_hwnd == nullptr)
    return TResult::Error("can't create window");

  return TResult::Okay();
}

void CWindow::Show() const
{
  ShowWindow(m_windowData.m_hwnd, true);
  UpdateWindow(m_windowData.m_hwnd);
}

void CWindow::StartLoop()
{
  MSG msg;
  ZeroMemory(&msg, sizeof(MSG));

  while (true)
  {
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      m_windowLoopCallback.OnTick();
    }
  }
}

//static
void CWindow::ExitApplication()
{
  PostQuitMessage(0);
}

//static
LRESULT CALLBACK CWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_KEYDOWN:
    {
      if (wParam == VK_ESCAPE)
      {
        ExitApplication();
        return 0;
      }

      //input::CKeyboard::OnKeyDown((unsigned int)wParam);
      break;
    }
    case WM_KEYUP:
    {
      //input::CKeyboard::OnKeyUp((unsigned int)wParam);
      break;
    }
    case WM_DESTROY:
    {
      ExitApplication();
      return 0;
    }
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}
}
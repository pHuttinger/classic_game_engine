//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "TestGame.h"

int main()
{
  cge::TWindowCreateInfo windowCreateInfo
  {
    .m_title      = "Test Application",
#ifndef _DEBUG
    .m_width      = 1920,
    .m_height     = 1080,
    .m_fullscreen = true,
#endif
  };

  cge::TInstanceCreateInfo createInfo
  {
    .m_windowCreateInfo = windowCreateInfo,
    .m_backend          = cge::EBackend::DX11,
    .m_pGame            = std::make_unique<CTestGame>(),
  };

  cge::CInstance instance;
  cge::TResult result = instance.Create(createInfo);
  if (result.IsError())
  {
    return -1;
  }

  instance.Run();

  return 0;
}
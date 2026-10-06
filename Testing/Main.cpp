//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "TestGame.h"

int main()
{
  cge::TWindowCreateInfo windowCreateInfo
  {
    .m_title = "Test Application",
  };

  cge::TInstanceCreateInfo createInfo
  {
    .m_windowCreateInfo = windowCreateInfo,
    .m_backend          = cge::rhi::EBackend::DX11,
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
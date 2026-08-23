//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include <Engine/Inc/Instance.h>

//----------------------------------------------------
// CTestGame
//----------------------------------------------------
class CTestGame : public cge::IGame
{
public:

  cge::TResult OnCreate(cge::CInstance& instance) override
  {
    return cge::TResult::Okay();
  }

  void OnTick(const float deltaTime) override
  {
  }
};

//----------------------------------------------------
// entry point
//----------------------------------------------------
int main()
{
  cge::TInstanceCreateInfo createInfo
  {
    .m_backend = cge::rhi::EBackend::DX11,
    .m_pGame   = std::make_unique<CTestGame>()
  };

  cge::CInstance instance;
  cge::TResult result = instance.Create(createInfo);
  if (result.IsError())
    return -1;

  instance.Run();

  return 0;
}
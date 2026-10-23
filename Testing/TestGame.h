//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include <Engine/Inc/Instance.h>

class CTestGame : public cge::IGame
{
public:

  cge::TResult OnCreate(cge::CInstance& instance) override;
  void OnTick(const float deltaTime) override;

private:

  cge::CInstance* m_pInstance = nullptr;
  cge::CActor* m_pBox = nullptr;
  cge::CActor* m_pMan = nullptr;
};
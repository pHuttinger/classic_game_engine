//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <chrono>

namespace cge
{
class CTimer final
{
public:

  CTimer();

  void Update();
  float GetDeltaTime() const;
  float GetEngineTime() const;

private:

  std::chrono::steady_clock::time_point m_lastFrameTime;
  float m_deltaTime;
};
}
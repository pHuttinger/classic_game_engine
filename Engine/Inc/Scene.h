//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Actor.h"
#include "Camera.h"

namespace cge
{
class CScene final
{
public:

  CScene(const glm::vec2& viewportSize);

  void AddActor(CActor* pActor);
  void RemoveActor(CActor* pActor);

  std::vector<CActor*>& GetActors() { return m_actors; }
  CCamera& GetCurrentCamera() { return m_camera; }

private:

  std::vector<CActor*> m_actors;
  CCamera m_camera;
};
}

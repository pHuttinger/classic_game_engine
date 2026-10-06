//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Scene.h"

namespace cge
{
CScene::CScene(const glm::vec2& viewportSize)
  : m_camera(viewportSize)
{
}

void CScene::AddActor(CActor* pActor)
{
  m_actors.push_back(pActor);
}

void CScene::RemoveActor(CActor* pActor)
{
  m_actors.erase(std::remove(m_actors.begin(), m_actors.end(), pActor), m_actors.end());
}
}
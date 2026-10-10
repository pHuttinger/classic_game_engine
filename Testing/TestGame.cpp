//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "TestGame.h"

cge::TResult CTestGame::OnCreate(cge::CInstance& instance)
{
  cge::CSceneManager& sceneManager = instance.GetSceneManager();
  cge::CAssetManager& assetManager = instance.GetAssetManager();

  cge::CScene* pScene = sceneManager.CreateScene("TestScene");
  sceneManager.SetCurrentScene("TestScene");

  cge::CStaticMesh* pStaticMesh = assetManager.CreateStaticMesh();
  
  m_pActor = assetManager.CreateActor();
  m_pActor->AddStaticMesh(pStaticMesh);
  pScene->AddActor(m_pActor);

  m_pActor2 = assetManager.CreateActor();
  m_pActor2->AddStaticMesh(pStaticMesh);
  pScene->AddActor(m_pActor2);

  cge::CCamera& camera = pScene->GetCurrentCamera();
  camera.GetTransform().GetPosition() = glm::vec3(0.0f, 0.0f, -5.0f);

  return cge::TResult::Okay();
}

void CTestGame::OnTick(const float deltaTime)
{
  static float rotationAngle = 0.0f;
  static float rotationAngle2 = 0.0f;
  const float rotationSpeed = 50.0f * deltaTime;
  m_pActor->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle += rotationSpeed), glm::vec3(1.0f, 1.0f, 1.0f));
  m_pActor2->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle2 -= rotationSpeed), glm::vec3(1.0f, 1.0f, 1.0f));
}
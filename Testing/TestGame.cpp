//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "TestGame.h"
#include <Engine/Inc/PresetMeshes.h>
#include <Common/Inc/FileSystem/Assimp.h>

cge::TResult CTestGame::OnCreate(cge::CInstance& instance)
{
  cge::CSceneManager& sceneManager = instance.GetSceneManager();
  cge::CAssetManager& assetManager = instance.GetAssetManager();

  cge::presets::CBox box;
  cge::TStaticMeshModel boxMeshModel;
  boxMeshModel.m_vertices     = box.GetVertices();
  boxMeshModel.m_indices      = box.GetIndices();
  boxMeshModel.m_textureNames = { "image.png" };

  cge::TActorModel boxModel;
  boxModel.m_staticMeshModels.push_back(boxMeshModel);
  if (cge::TResult result = assetManager.CreateActor(boxModel, m_pBox); result.IsError())
  {
    return result;
  }

  m_pBox->GetTransform().GetPosition().y += 75.0f;
  m_pBox->GetTransform().GetPosition().x += 75.0f;
  m_pBox->GetTransform().GetScale() *= 20.0f;

  cge::filesystem::CAssimp assimp;

  cge::TActorModel manModel;
  assimp.LoadActorFromFile("models/male/scene.gltf", manModel);
  if (cge::TResult result = assetManager.CreateActor(manModel, m_pMan); result.IsError())
  {
    return result;
  }

  m_pMan->GetTransform().GetScale() *= 0.02f;

  cge::CScene* pScene = sceneManager.CreateScene("TestScene");
  pScene->AddActor(m_pMan);
  m_pMan->AddChild(m_pBox);

  cge::CCamera& camera = pScene->GetCurrentCamera();
  camera.GetTransform().GetPosition() = glm::vec3(0.0f, 2.0f, -5.0f);

  return cge::TResult::Okay();
}

void CTestGame::OnTick(const float deltaTime)
{
  static float rotationAngle = 0.0f;
  const  float rotationSpeed = 50.0f * deltaTime;

  m_pMan->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle += rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
  m_pBox->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle * 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}
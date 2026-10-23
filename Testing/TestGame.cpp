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

  //cge::presets::CBox box;
  //cge::TStaticMeshModel staticMeshModel;
  //staticMeshModel.m_vertices     = box.GetVertices();
  //staticMeshModel.m_indices      = box.GetIndices();
  //staticMeshModel.m_textureNames = { "box.jpg" };

  //cge::TActorModel actorModel;
  //actorModel.m_staticMeshModels.push_back(staticMeshModel);

  cge::filesystem::CAssimp assimp;

  cge::TActorModel actorModel;
  assimp.LoadActorFromFile("models/male/scene.gltf", actorModel);

  if (cge::TResult result = assetManager.CreateActor(actorModel, m_pActor); result.IsError())
  {
    return result;
  }

  m_pActor->GetTransform().GetScale() *= 0.02f;

  cge::CScene* pScene = sceneManager.CreateScene("TestScene");
  pScene->AddActor(m_pActor);

  cge::CCamera& camera = pScene->GetCurrentCamera();
  camera.GetTransform().GetPosition() = glm::vec3(0.0f, 2.0f, -5.0f);

  return cge::TResult::Okay();
}

void CTestGame::OnTick(const float deltaTime)
{
  static float rotationAngle = 0.0f;
  const  float rotationSpeed = 50.0f * deltaTime;

  m_pActor->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle += rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
}
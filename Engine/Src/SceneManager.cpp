//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/SceneManager.h"
#include "../Inc/Instance.h"

namespace cge
{
CSceneManager::CSceneManager(CInstance& instance)
  : m_instance(instance)
{
}

CScene* CSceneManager::CreateScene(const std::string& name)
{
  if (m_scenes.find(name) != m_scenes.end())
  {
    return m_scenes[name].get();
  }

  const glm::vec2& viewportSize
  {
    m_instance.m_window.GetWindowCreateInfo().m_width,
    m_instance.m_window.GetWindowCreateInfo().m_height,
  };

  auto pScene = std::make_unique<CScene>(viewportSize);
  CScene* scenePtr = pScene.get();
  m_scenes.emplace(name, std::move(pScene));
  return scenePtr;
}

void CSceneManager::SetCurrentScene(const std::string& name)
{
  if (m_scenes.find(name) != m_scenes.end())
  {
    m_pCurrentScene = m_scenes[name].get();
  }
}

void CSceneManager::EvaluateCurrentScene()
{
  if (m_pCurrentScene == nullptr)
  {
    return;
  }

  CCamera& camera = m_pCurrentScene->GetCurrentCamera();
  camera.Update();

  for (CActor* pActor : m_pCurrentScene->GetActors())
  {
    for (const TStaticMeshData& staticMeshData : pActor->GetStaticMeshes())
    {
      //TODO somehow we have to evaluate childrens transformations and apply them to the static meshes
      CStaticMesh* pStaticMesh = staticMeshData.m_pStaticMesh;
      render::CShaderData* pShaderData = staticMeshData.m_pShaderData.get();

      staticMeshData.m_pStaticMesh->Update(pShaderData, camera, pActor->GetTransform());

      render::TDrawCall drawCall
      {
        .m_pMeshData  = pStaticMesh->GetMeshData(),
        .m_shaderData = { pShaderData }
      };

      m_instance.GetRenderProxy().AddDrawCall(drawCall);
    }
  }
}
}
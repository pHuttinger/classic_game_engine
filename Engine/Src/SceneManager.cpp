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

  m_scenes.emplace(name, std::make_unique<CScene>(viewportSize));
  m_pCurrentScene = m_scenes[name].get();
  return m_pCurrentScene;
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

  render::CFrameInput& frameInput = m_instance.GetRenderProxy().GetFrameInput();

  CCamera& camera = m_pCurrentScene->GetCurrentCamera();

  frameInput.SetCameraPosition(camera.GetTransform().GetPosition());

  for (CActor* pActor : m_pCurrentScene->GetActors())
  {
    EvaluateActor(camera, pActor, glm::mat4(1.0f));
  }
}

void CSceneManager::EvaluateActor(CCamera& camera, CActor* pActor, const glm::mat4& parentMatrix)
{
  glm::mat4 model = parentMatrix * pActor->GetTransform().GetModelMatrix();

  for (CActor* pChild : pActor->GetChilds())
  {
    EvaluateActor(camera, pChild, model);
  }

  for (const TStaticMeshContext& staticMeshContext : pActor->GetStaticMeshes())
  {
    EvaluateStaticMesh(camera, model, staticMeshContext);
  }
}

void CSceneManager::EvaluateStaticMesh(CCamera& camera, const glm::mat4& model, const TStaticMeshContext& staticMeshContext)
{
  CStaticMesh* pStaticMesh = staticMeshContext.m_pStaticMesh;
  render::CShaderData* pVertexShaderData = staticMeshContext.m_pVertexShaderData.get();

  staticMeshContext.m_pStaticMesh->Update(pVertexShaderData, camera, model);

  render::TDrawCall drawCall
  {
    .m_pDrawItem  = pStaticMesh->GetDrawItem(),
    .m_shaderData = { pVertexShaderData }
  };

  m_instance.GetRenderProxy().GetFrameInput().AddDrawCall(drawCall);
}
}
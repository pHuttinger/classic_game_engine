//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Scene.h"

namespace cge
{
class CSceneManager final
{
friend class CInstance;

public:

  CSceneManager(CInstance& instance);

  CScene* CreateScene(const std::string& name);
  void SetCurrentScene(const std::string& name);

private:

  void EvaluateCurrentScene();
  void EvaluateActor(CCamera& camera, CActor* pActor, const glm::mat4& parentMatrix);
  void EvaluateStaticMesh(CCamera& camera, const glm::mat4& model, const TStaticMeshData& staticMeshData);

  CInstance& m_instance;
  std::unordered_map<std::string, std::unique_ptr<CScene>> m_scenes;
  CScene* m_pCurrentScene = nullptr;
};
}
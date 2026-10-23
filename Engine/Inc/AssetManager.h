//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Actor.h"
#include <Common/Inc/ImportModel.h>

namespace cge
{
class CInstance;

//----------------------------------------------------
// TAssetStore
//----------------------------------------------------
struct TAssetStore final
{
  std::vector<std::unique_ptr<CStaticMesh>> m_staticMeshes;
  std::vector<std::unique_ptr<CActor>> m_actors;
};

//----------------------------------------------------
// CAssetManager
//----------------------------------------------------
class CAssetManager final
{
public:

  CAssetManager(CInstance& instance);

  CActor* CreateEmptyActor();
  TResult CreateActor(TActorModel& model, CActor*& pActor);
  void    DestroyActor(CActor* pActor);
  TResult CreateStaticMesh(TStaticMeshCreateInfo& createInfo, CStaticMesh*& pStaticMesh);
  TResult CreateStaticMesh(TMeshModel& model, CStaticMesh*& pStaticMesh);
  void    DestroyStaticMesh(CStaticMesh* pStaticMesh);

private:

  TResult CreateActorsMeshes(TActorModel& model, CActor* pActor);
  TStaticMeshCreateInfo StaticMeshCreateInfoFromMeshModel(TMeshModel& meshModel) const;

  CInstance& m_instance;
  TAssetStore m_assetStore;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Actor.h"

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

  CActor* CreateActor();
  void DestroyActor(CActor* pActor);

  CStaticMesh* CreateStaticMesh();
  void DestroyStaticMesh(CStaticMesh* pStaticMesh);

private:

  CInstance& m_instance;
  TAssetStore m_assetStore;
};
}
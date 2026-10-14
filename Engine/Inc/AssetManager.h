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
struct TStaticMeshCreateInfo final
{
  TDataHandle m_vertexData;
  TDataHandle m_indexData;
  size_t      m_indexCount = 0U;
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

  CStaticMesh* CreateStaticMesh(const TStaticMeshCreateInfo& createInfo);
  void DestroyStaticMesh(CStaticMesh* pStaticMesh);

private:

  CInstance& m_instance;
  TAssetStore m_assetStore;
};
}
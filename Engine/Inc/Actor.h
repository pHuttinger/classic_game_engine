//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Transform.h"
#include "StaticMesh.h"

namespace cge
{
class CInstance;

//----------------------------------------------------
// TStaticMeshData
//----------------------------------------------------
struct TStaticMeshData final
{
  CStaticMesh* m_pStaticMesh = nullptr;
  std::shared_ptr<render::CShaderData> m_pShaderData;
};

//----------------------------------------------------
// TStaticMeshData
//----------------------------------------------------
class CActor final
{
public:

  CActor(CInstance& instance);

  TResult AddStaticMesh(CStaticMesh* pStaticMesh);
  void AddChild(CActor* pChild);

  CTransform& GetTransform() { return m_transform; }
  const std::vector<TStaticMeshData>& GetStaticMeshes() const { return m_staticMeshes; }

private:

  CInstance& m_instance;
  CTransform m_transform;
  std::vector<TStaticMeshData> m_staticMeshes;
  std::vector<CActor*> m_childs;
};
}

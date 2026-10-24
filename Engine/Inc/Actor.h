//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Transform.h"
#include "StaticMesh.h"
#include "SkinnedMesh.h"

namespace cge
{
class CInstance;

//----------------------------------------------------
// TStaticMeshContext
//----------------------------------------------------
struct TStaticMeshContext final
{
  CStaticMesh* m_pStaticMesh = nullptr;
  std::shared_ptr<render::CShaderData> m_pVertexShaderData;
};

//----------------------------------------------------
// TSkinnedMeshContext
//----------------------------------------------------
struct TSkinnedMeshContext final
{
  CSkinnedMesh* m_pSkinnedMesh = nullptr;
  std::shared_ptr<render::CShaderData> m_pVertexShaderData;
};

//----------------------------------------------------
// TStaticMeshContext
//----------------------------------------------------
class CActor final
{
public:

  CActor(CInstance& instance);

  TResult AddStaticMesh(CStaticMesh* pStaticMesh);
  TResult AddSkinnedMesh(CSkinnedMesh* pSkinnedMesh);
  void AddChild(CActor* pChild);

  CTransform& GetTransform() { return m_transform; }
  const std::vector<TStaticMeshContext>& GetStaticMeshes() const { return m_staticMeshes; }
  const std::vector<TSkinnedMeshContext>& GetSkinnedMeshes() const { return m_skinnedMeshes; }
  const std::vector<CActor*> GetChilds() const { return m_childs; }

private:

  CInstance&                       m_instance;
  CTransform                       m_transform;
  std::vector<TStaticMeshContext>  m_staticMeshes;
  std::vector<TSkinnedMeshContext> m_skinnedMeshes;
  std::vector<CActor*>             m_childs;
};
}

//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Actor.h"
#include "../Inc/Instance.h"

namespace cge
{
CActor::CActor(CInstance& instance)
  : m_instance(instance)
{
}

TResult CActor::AddStaticMesh(CStaticMesh* pStaticMesh)
{
  std::shared_ptr<render::CShaderData> pVertexShaderData;
  CGE_TRY(pStaticMesh->GetVertexShaderData(m_instance.GetRenderProxy().GetRenderer(), pVertexShaderData));

  TStaticMeshContext staticMeshContext
  {
    .m_pStaticMesh       = pStaticMesh,
    .m_pVertexShaderData = pVertexShaderData,
  };

  m_staticMeshes.push_back(staticMeshContext);
  return TResult::Okay();
}

TResult CActor::AddSkinnedMesh(CSkinnedMesh* pSkinnedMesh)
{
  std::shared_ptr<render::CShaderData> pVertexShaderData;
  CGE_TRY(pSkinnedMesh->GetVertexShaderData(m_instance.GetRenderProxy().GetRenderer(), pVertexShaderData));

  TSkinnedMeshContext skinnedMeshContext
  {
    .m_pSkinnedMesh      = pSkinnedMesh,
    .m_pVertexShaderData = pVertexShaderData,
  };

  m_skinnedMeshes.push_back(skinnedMeshContext);
  return TResult::Okay();
}

void CActor::AddChild(CActor* pChild)
{
  m_childs.push_back(pChild);
}
}
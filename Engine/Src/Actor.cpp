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
  render::CRenderer& renderer = m_instance.GetRenderProxy().GetRenderer();
  auto pShaderData = std::make_shared<render::CShaderData>(renderer);

  render::TShaderDataCreateInfo shaderDataCreateInfo
  {
    .m_size        = sizeof(TStaticMeshVertexShaderData),
    .m_destination = render::EShaderDataDestination::Vertex,
  };

  CGE_TRY(pShaderData->Initialize(shaderDataCreateInfo));

  TStaticMeshContext staticMeshContext
  {
    .m_pStaticMesh = pStaticMesh,
    .m_pShaderData = std::move(pShaderData),
  };

  m_staticMeshes.push_back(staticMeshContext);
  return TResult::Okay();
}

void CActor::AddChild(CActor* pChild)
{
  m_childs.push_back(pChild);
}
}
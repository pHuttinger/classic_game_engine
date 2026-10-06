//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Transform.h"
#include "StaticMesh.h"

namespace cge
{
class CActor final
{
public:

  void AddStaticMesh(CStaticMesh* pStaticMesh);
  void AddChild(CActor* pChild);

  CTransform& GetTransform() { return m_transform; }
  const std::vector<CStaticMesh*>& GetStaticMeshes() const { return m_staticMeshes; }

private:

  CTransform m_transform;
  std::vector<CStaticMesh*> m_staticMeshes;
  std::vector<CActor*> m_childs;
};
}

//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Actor.h"

namespace cge
{
void CActor::AddStaticMesh(CStaticMesh* pStaticMesh)
{
  m_staticMeshes.push_back(pStaticMesh);
}

void CActor::AddChild(CActor* pChild)
{
  m_childs.push_back(pChild);
}
}
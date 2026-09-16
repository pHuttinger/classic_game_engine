//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>
#include "Mesh.h"

namespace cge::render
{
class CFrameInput final
{
public:

  CFrameInput();

  void Reset();

  glm::vec4 m_clearColor;
  std::vector<CMesh*> m_pMeshes;
};
}
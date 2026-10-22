//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::presets
{
//----------------------------------------------------
// CBox
//----------------------------------------------------
class CBox final
{
public:

  std::vector<TVertexStaticMesh> GetVertices() const;
  std::vector<uint32_t> GetIndices() const;
};
}
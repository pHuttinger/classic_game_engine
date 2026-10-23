//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/ImportModel.h>

namespace cge::presets
{
//----------------------------------------------------
// CBox
//----------------------------------------------------
class CBox final
{
public:

  std::vector<TVertexModel> GetVertices() const;
  std::vector<uint32_t> GetIndices() const;
};
}
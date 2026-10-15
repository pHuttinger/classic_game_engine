//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Common.h>

namespace cge
{
//----------------------------------------------------
// IPipeline
//----------------------------------------------------
class CTestBox final
{
public:

  std::vector<render::TVertexStaticMesh> GetVertices() const;
  std::vector<uint32_t> GetIndices() const;
};
}
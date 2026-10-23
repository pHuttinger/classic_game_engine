//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../ImportModel.h"

class aiMesh;

namespace cge::filesystem
{
class CAssimp final
{
public:

  TResult LoadActorFromFile(const std::filesystem::path& filename, TActorModel& model);

private:

  TMeshModel ExtractMeshModel(aiMesh* pMesh) const;
  TVertexModel ExtractVertex(aiMesh* pMesh, const size_t vertexIndex) const;
};
}

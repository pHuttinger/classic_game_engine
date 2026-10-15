//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/PresetMeshes.h"

namespace cge
{
std::vector<render::TVertexStaticMesh> CTestBox::GetVertices() const
{
  return
  {
    render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},

    render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},

    render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},

    render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},

    render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},

    render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}
  };
}

std::vector<uint32_t> CTestBox::GetIndices() const
{
  return
  {
    0,  1,  2,
    0,  2,  3,

    4,  5,  6,
    4,  6,  7,

    8,  9, 10,
    8, 10, 11,

    12, 13, 14,
    12, 14, 15,

    16, 17, 18,
    16, 18, 19,

    20, 21, 22,
    20, 22, 23
  };
}
}
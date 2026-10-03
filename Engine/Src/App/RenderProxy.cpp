/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/App/RenderProxy.h"

namespace cge
{
CRenderProxy::CRenderProxy()
{
}

TResult CRenderProxy::Initialize(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(m_renderer.Initialize(createInfo));

  //TODO remove
  std::vector<render::TVertexStaticMesh> vertices =
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

    render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},

    render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, {1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}
  };


  std::vector<uint32_t> indices =
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

  render::TMeshCreateInfo mci;
  mci.m_pixelShaderName    = "PS_StaticMesh";
  mci.m_vertexShaderName   = "VS_StaticMesh";
  mci.m_vertexType         = render::EVertexType::StaticMesh;
  mci.m_textureName        = "image.png";
  mci.m_vertexData.m_size  = vertices.size() * sizeof(render::TVertexStaticMesh);
  mci.m_vertexData.m_pData = vertices.data();
  mci.m_indexData.m_size   = indices.size() * sizeof(uint32_t);
  mci.m_indexData.m_pData  = indices.data();
  mci.m_indexCount         = static_cast<uint32_t>(indices.size());
  mci.m_stride             = sizeof(render::TVertexStaticMesh);
  mci.m_rasterizerState    = render::ERasterizerState::Solid;
  CGE_TRY(CreateStaticMesh(mci, m_pStaticMesh));
  //TODO remove

  return TResult::Okay();
}

TResult CRenderProxy::CreateStaticMesh(const render::TMeshCreateInfo& createInfo, std::unique_ptr<CStaticMesh>& pStaticMesh)
{
  pStaticMesh = std::make_unique<CStaticMesh>();
  CGE_TRY(pStaticMesh->Initialize(m_renderer, createInfo));
  return TResult::Okay();
}

void CRenderProxy::RenderFrame()
{
  //TODO remove
  m_frameInput.AddDrawCall({ m_pStaticMesh->GetMeshData(), { m_pStaticMesh->GetShaderData() } });
  //TODO remove
  m_renderer.RenderFrame(m_frameInput);
  m_frameInput.Reset();
}
}
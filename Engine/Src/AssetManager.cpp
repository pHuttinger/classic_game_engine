//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/AssetManager.h"
#include "../Inc/Instance.h"

namespace cge
{
CAssetManager::CAssetManager(CInstance& instance)
  : m_instance(instance)
{
}

CActor* CAssetManager::CreateActor()
{
  auto pActor = std::make_unique<CActor>();
  m_assetStore.m_actors.push_back(std::move(pActor));
  return m_assetStore.m_actors.back().get();
}

void CAssetManager::DestroyActor(CActor* pActor)
{
  auto removeCondition = [pActor](const std::unique_ptr<CActor>& a)
  {
    return a.get() == pActor;
  };

  auto removeIter = std::remove_if(
    m_assetStore.m_actors.begin(),
    m_assetStore.m_actors.end(),
    removeCondition);

  m_assetStore.m_actors.erase(
    removeIter,
    m_assetStore.m_actors.end());
}

CStaticMesh* CAssetManager::CreateStaticMesh()
{
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

    render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},

    render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}
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
  //TODO remove

  //TODO Get render::CMeshData from cache here!
  auto pStaticMesh = std::make_unique<CStaticMesh>();
  TResult result = pStaticMesh->Initialize(m_instance.GetRenderProxy().GetRenderer(), mci);
  if (result.IsError())
  {
    return nullptr;
  }

  m_assetStore.m_staticMeshes.push_back(std::move(pStaticMesh));
  return m_assetStore.m_staticMeshes.back().get();
}

void CAssetManager::DestroyStaticMesh(CStaticMesh* pStaticMesh)
{
  auto removeCondition = [pStaticMesh](const std::unique_ptr<CStaticMesh>& a)
  {
    return a.get() == pStaticMesh;
  };

  auto removeIter = std::remove_if(
    m_assetStore.m_staticMeshes.begin(),
    m_assetStore.m_staticMeshes.end(),
    removeCondition);

  m_assetStore.m_staticMeshes.erase(
    removeIter,
    m_assetStore.m_staticMeshes.end());
}
}
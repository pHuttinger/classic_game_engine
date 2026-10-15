//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/AssetManager.h"
#include "../Inc/Instance.h"
#include "../Inc/PresetMeshes.h"

namespace cge
{
CAssetManager::CAssetManager(CInstance& instance)
  : m_instance(instance)
{
}

CActor* CAssetManager::CreateActor()
{
  auto pActor = std::make_unique<CActor>(m_instance);
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

CStaticMesh* CAssetManager::CreateStaticMesh(const TStaticMeshCreateInfo& createInfo)
{
  render::TDrawItemCreateInfo drawItem
  {
    .m_vertexType       = render::EVertexType::StaticMesh,
    .m_vertexShaderName = "VS_StaticMesh",
    .m_pixelShaderName  = "PS_StaticMesh",
    .m_textureName      = "image.png",
    .m_vertexData       = createInfo.m_vertexData,
    .m_indexData        = createInfo.m_indexData,
    .m_indexCount       = createInfo.m_indexCount,
    .m_stride           = sizeof(render::TVertexStaticMesh),
    .m_rasterizerState  = render::ERasterizerState::Solid,
  };

  //TODO Get render::CDrawItem from cache here!
  auto pStaticMesh = std::make_unique<CStaticMesh>();
  TResult result = pStaticMesh->Initialize(m_instance.GetRenderProxy().GetRenderer(), drawItem);
  if (result.IsError())
  {
    return nullptr;
  }

  m_assetStore.m_staticMeshes.push_back(std::move(pStaticMesh));
  return m_assetStore.m_staticMeshes.back().get();
}

CStaticMesh* CAssetManager::CreateStaticMesh_TestBox()
{
  CTestBox testBox;
  std::vector<render::TVertexStaticMesh> vertices = testBox.GetVertices();
  std::vector<uint32_t> indices = testBox.GetIndices();

  TStaticMeshCreateInfo createInfo
  {
    .m_vertexData =
    {
      .m_size  = vertices.size() * sizeof(render::TVertexStaticMesh),
      .m_pData = vertices.data(),
    },
    .m_indexData =
    {
      .m_size  = indices.size() * sizeof(uint32_t),
      .m_pData = indices.data(),
    },
    .m_indexCount = indices.size(),
  };

  return CreateStaticMesh(createInfo);
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
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

CActor* CAssetManager::CreateEmptyActor()
{
  m_assetStore.m_actors.push_back(std::make_unique<CActor>(m_instance));
  return m_assetStore.m_actors.back().get();
}

TResult CAssetManager::CreateActor(TActorModel& model, CActor*& pActor)
{
  pActor = CreateEmptyActor();

  for (auto& staticMeshModel : model.m_staticMeshModels)
  {
    CStaticMesh* pStaticMesh = nullptr;
    CGE_TRY(CreateStaticMesh(staticMeshModel, pStaticMesh));
    CGE_TRY(pActor->AddStaticMesh(pStaticMesh));
  }

  return TResult::Okay();
}

void CAssetManager::DestroyActor(CActor* pActor)
{
  auto removeCondition = [pActor](const std::unique_ptr<CActor>& a)
  {
    return a.get() == pActor;
  };

  auto removeIter = std::remove_if
  (
    m_assetStore.m_actors.begin(),
    m_assetStore.m_actors.end(),
    removeCondition
  );

  m_assetStore.m_actors.erase
  (
    removeIter,
    m_assetStore.m_actors.end()
  );
}

TResult CAssetManager::CreateStaticMesh(const TStaticMeshCreateInfo& createInfo, CStaticMesh*& pStaticMesh)
{
  std::vector<TVertexAttribute> vertexAttributes =
  {
     {EVertexAttributeUsage::Position, EVertexAttributeFormat::Float3},
     {EVertexAttributeUsage::Normal  , EVertexAttributeFormat::Float3},
     {EVertexAttributeUsage::Texcoord, EVertexAttributeFormat::Float2},
  };

  render::TDrawItemCreateInfo drawItem
  {
    .m_vertexShaderName = "VS_StaticMesh",
    .m_pixelShaderName  = "PS_StaticMesh",
    .m_vertexAttributes = vertexAttributes,
    .m_vertexData       = createInfo.m_vertexData,
    .m_indexData        = createInfo.m_indexData,
    .m_indexCount       = createInfo.m_indexCount,
    .m_stride           = sizeof(TVertexStaticMesh),
    .m_rasterizerState  = ERasterizerState::Solid,
    .m_textureNames     = createInfo.m_textureNames,
  };

  auto staticMesh = std::make_unique<CStaticMesh>();
  CGE_TRY(staticMesh->Initialize(m_instance.GetRenderProxy().GetRenderer(), drawItem));

  pStaticMesh = staticMesh.get();
  m_assetStore.m_staticMeshes.push_back(std::move(staticMesh));

  return TResult::Okay();
}

TResult CAssetManager::CreateStaticMesh(TStaticMeshModel& model, CStaticMesh*& pStaticMesh)
{
  TStaticMeshCreateInfo createInfo = CreateInfoFromImportModel(model);
  CGE_TRY(CreateStaticMesh(createInfo, pStaticMesh));
  return TResult::Okay();
}

void CAssetManager::DestroyStaticMesh(CStaticMesh* pStaticMesh)
{
  auto removeCondition = [pStaticMesh](const std::unique_ptr<CStaticMesh>& a)
  {
    return a.get() == pStaticMesh;
  };

  auto removeIter = std::remove_if
  (
    m_assetStore.m_staticMeshes.begin(),
    m_assetStore.m_staticMeshes.end(),
    removeCondition
  );

  m_assetStore.m_staticMeshes.erase
  (
    removeIter,
    m_assetStore.m_staticMeshes.end()
  );
}

TStaticMeshCreateInfo CAssetManager::CreateInfoFromImportModel(TStaticMeshModel& model)
{
  TDataHandle vertexData
  {
    .m_size  = model.m_vertices.size() * sizeof(TVertexStaticMesh),
    .m_pData = model.m_vertices.data(),
  };

  TDataHandle indexData
  {
    .m_size  = model.m_indices.size() * sizeof(uint32_t),
    .m_pData = model.m_indices.data(),
  };

  return
  {
    .m_vertexData   = vertexData,
    .m_indexData    = indexData,
    .m_indexCount   = model.m_indices.size(),
    .m_textureNames = model.m_textureNames,
  };
}
}

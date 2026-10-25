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

  CGE_TRY(CreateActorsMeshes(model, pActor));

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

TResult CAssetManager::CreateStaticMesh(TStaticMeshCreateInfo& createInfo, CStaticMesh*& pStaticMesh)
{
  TDataHandle vertexData
  {
    .m_size  = createInfo.m_vertices.size() * sizeof(TVertexStaticMesh),
    .m_pData = createInfo.m_vertices.data(),
  };

  TDataHandle indexData
  {
    .m_size  = createInfo.m_indices.size() * sizeof(uint32_t),
    .m_pData = createInfo.m_indices.data(),
  };

  render::TDrawItemCreateInfo drawItem
  {
    .m_vertexShaderName = CStaticMesh::GetVertexShaderName(),
    .m_pixelShaderName  = CStaticMesh::GetPixelShaderName(),
    .m_vertexAttributes = CStaticMesh::GetVertexAttributes(),
    .m_vertexData       = vertexData,
    .m_indexData        = indexData,
    .m_indexCount       = createInfo.m_indices.size(),
    .m_stride           = sizeof(TVertexStaticMesh),
    .m_textureNames     = createInfo.m_textureNames,
  };

  auto staticMesh = std::make_unique<CStaticMesh>();
  CGE_TRY(staticMesh->Initialize(m_instance.GetRenderProxy().GetRenderer(), drawItem));

  pStaticMesh = staticMesh.get();
  m_assetStore.m_staticMeshes.push_back(std::move(staticMesh));

  return TResult::Okay();
}

TResult CAssetManager::CreateStaticMesh(TMeshModel& model, CStaticMesh*& pStaticMesh)
{
  TStaticMeshCreateInfo createInfo = StaticMeshCreateInfoFromMeshModel(model);
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

TResult CAssetManager::CreateSkinnedMesh(TSkinnedMeshCreateInfo& createInfo, CSkinnedMesh*& pSkinnedMesh)
{
  TDataHandle vertexData
  {
    .m_size  = createInfo.m_vertices.size() * sizeof(TVertexSkinnedMesh),
    .m_pData = createInfo.m_vertices.data(),
  };

  TDataHandle indexData
  {
    .m_size  = createInfo.m_indices.size() * sizeof(uint32_t),
    .m_pData = createInfo.m_indices.data(),
  };

  render::TDrawItemCreateInfo drawItem
  {
    .m_vertexShaderName = CSkinnedMesh::GetVertexShaderName(),
    .m_pixelShaderName  = CSkinnedMesh::GetPixelShaderName(),
    .m_vertexAttributes = CSkinnedMesh::GetVertexAttributes(),
    .m_vertexData       = vertexData,
    .m_indexData        = indexData,
    .m_indexCount       = createInfo.m_indices.size(),
    .m_stride           = sizeof(TVertexSkinnedMesh),
    .m_textureNames     = createInfo.m_textureNames,
  };

  auto skinnedMesh = std::make_unique<CSkinnedMesh>();
  CGE_TRY(skinnedMesh->Initialize(m_instance.GetRenderProxy().GetRenderer(), drawItem));

  skinnedMesh->SetBoneTransforms(createInfo.m_staticBoneTransforms);
  skinnedMesh->m_animations = createInfo.m_animations;

  pSkinnedMesh = skinnedMesh.get();
  m_assetStore.m_skinnedMeshes.push_back(std::move(skinnedMesh));

  return TResult::Okay();
}

TResult CAssetManager::CreateSkinnedMesh(TMeshModel& model, CSkinnedMesh*& pSkinnedMesh)
{
  TSkinnedMeshCreateInfo createInfo = SkinnedMeshCreateInfoFromMeshModel(model);
  CGE_TRY(CreateSkinnedMesh(createInfo, pSkinnedMesh));
  return TResult::Okay();
}

void CAssetManager::DestroySkinnedMesh(CSkinnedMesh* pSkinnedMesh)
{
  auto removeCondition = [pSkinnedMesh](const std::unique_ptr<CSkinnedMesh>& a)
  {
    return a.get() == pSkinnedMesh;
  };

  auto removeIter = std::remove_if
  (
    m_assetStore.m_skinnedMeshes.begin(),
    m_assetStore.m_skinnedMeshes.end(),
    removeCondition
  );

  m_assetStore.m_skinnedMeshes.erase
  (
    removeIter,
    m_assetStore.m_skinnedMeshes.end()
  );
}

TResult CAssetManager::CreateActorsMeshes(TActorModel& model, CActor* pActor)
{
  for (auto& meshModel : model.m_meshModels)
  {
    switch (meshModel.m_meshType)
    {
      case EMeshType::Static:
      {
        CStaticMesh* pStaticMesh = nullptr;
        CGE_TRY(CreateStaticMesh(meshModel, pStaticMesh));
        CGE_TRY(pActor->AddStaticMesh(pStaticMesh));
        break;
      }
      case EMeshType::Skinned:
      {
        CSkinnedMesh* pSkinnedMesh = nullptr;
        CGE_TRY(CreateSkinnedMesh(meshModel, pSkinnedMesh));
        CGE_TRY(pActor->AddSkinnedMesh(pSkinnedMesh));
        break;
      }
    }
  }

  return TResult::Okay();
}

TStaticMeshCreateInfo CAssetManager::StaticMeshCreateInfoFromMeshModel(TMeshModel& meshModel) const
{
  TStaticMeshCreateInfo createInfo
  {
    .m_indices      = meshModel.m_indices,
    .m_textureNames = meshModel.m_textureNames,
  };

  for (auto& vertexModel : meshModel.m_vertices)
  {
    TVertexStaticMesh vertex
    {
      .m_position = vertexModel.m_position,
      .m_normal   = vertexModel.m_normal,
      .m_texcoord = vertexModel.m_texcoord,
    };

    createInfo.m_vertices.push_back(vertex);
  }

  return createInfo;
}

TSkinnedMeshCreateInfo CAssetManager::SkinnedMeshCreateInfoFromMeshModel(TMeshModel& meshModel) const
{
  TSkinnedMeshCreateInfo createInfo
  {
    .m_indices              = meshModel.m_indices,
    .m_textureNames         = meshModel.m_textureNames,
    .m_staticBoneTransforms = meshModel.m_staticBoneTransforms,
    .m_animations           = meshModel.m_animations,
  };

  for (auto& vertexModel : meshModel.m_vertices)
  {
    TVertexSkinnedMesh vertex
    {
      .m_position    = vertexModel.m_position,
      .m_normal      = vertexModel.m_normal,
      .m_texcoord    = vertexModel.m_texcoord,
      .m_boneIndices = vertexModel.m_boneIndices,
      .m_boneWeights = vertexModel.m_boneWeights,
    };

    createInfo.m_vertices.push_back(vertex);
  }

  return createInfo;
}
}

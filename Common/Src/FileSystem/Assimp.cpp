//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/FileSystem/Assimp.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp-vc143-mt.lib")

namespace cge::filesystem
{
TResult CAssimp::LoadActorFromFile(const std::filesystem::path& filename, TActorModel& model)
{
  Assimp::Importer importer;

  importer.SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 4);

  uint32_t importFlags =
    aiProcess_Triangulate      |
    aiProcess_GenNormals       |
    aiProcess_CalcTangentSpace |
    aiProcess_FlipUVs          |
    aiProcess_LimitBoneWeights |
    aiProcess_GlobalScale;

  const aiScene* pScene = importer.ReadFile(filename.string(), importFlags);
  if (pScene == nullptr)
  {
    return TResult::Error("scene is NULL");
  }

  for (size_t i = 0; i < pScene->mNumMeshes; i++)
  {
    aiMesh* pMesh = pScene->mMeshes[i];

    TMeshModel meshModel = ExtractMeshModel(pMesh);
    if (pMesh->HasBones())
    {
      meshModel.m_meshType = EMeshType::Skinned;
    }

    //TODO don't do it so
    meshModel.m_textureNames = { "models/running/texture.png" };

    model.m_meshModels.push_back(meshModel);
  }

  return TResult::Okay();
}

TMeshModel CAssimp::ExtractMeshModel(aiMesh* pMesh) const
{
  std::vector<TVertexModel> vertices;
  std::vector<uint32_t> indices;

  vertices.reserve(pMesh->mNumVertices);

  for (size_t i = 0; i < pMesh->mNumVertices; i++)
  {
    vertices.push_back(ExtractVertex(pMesh, i));
  }

  for (size_t i = 0; i < pMesh->mNumFaces; i++)
  {
    const aiFace& face = pMesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  return
  {
    .m_vertices = vertices,
    .m_indices  = indices,
  };
}

TVertexModel CAssimp::ExtractVertex(aiMesh* pMesh, const size_t vertexIndex) const
{
  TVertexModel vertex{};

  vertex.m_position.x = pMesh->mVertices[vertexIndex].x;
  vertex.m_position.y = pMesh->mVertices[vertexIndex].y;
  vertex.m_position.z = pMesh->mVertices[vertexIndex].z;

  if (pMesh->HasNormals())
  {
    vertex.m_normal.x = pMesh->mNormals[vertexIndex].x;
    vertex.m_normal.y = pMesh->mNormals[vertexIndex].y;
    vertex.m_normal.z = pMesh->mNormals[vertexIndex].z;
  }

  if (pMesh->HasTextureCoords(0U))
  {
    vertex.m_texcoord.x = pMesh->mTextureCoords[0U][vertexIndex].x;
    vertex.m_texcoord.y = pMesh->mTextureCoords[0U][vertexIndex].y;
  }

  return vertex;
}
}
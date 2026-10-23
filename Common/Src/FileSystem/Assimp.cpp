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

  const aiScene* pScene = importer.ReadFile(
    filename.string(),
    aiProcess_Triangulate      |
    aiProcess_GenNormals       |
    aiProcess_CalcTangentSpace |
    aiProcess_FlipUVs          |
    aiProcess_GlobalScale
  );

  for (size_t i = 0; i < pScene->mNumMeshes; i++)
  {
    aiMesh* pMesh = pScene->mMeshes[i];

    model.m_staticMeshModels.push_back(ExtractStaticMeshModel(pMesh));
  }

  return TResult::Okay();
}

TStaticMeshModel CAssimp::ExtractStaticMeshModel(aiMesh* mesh) const
{
  std::vector<TVertexStaticMesh> vertices;
  std::vector<uint32_t> indices;

  vertices.reserve(mesh->mNumVertices);

  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    TVertexStaticMesh vertex{};

    vertex.m_position.x = mesh->mVertices[i].x;
    vertex.m_position.y = mesh->mVertices[i].y;
    vertex.m_position.z = mesh->mVertices[i].z;

    if (mesh->HasNormals())
    {
      vertex.m_normal.x = mesh->mNormals[i].x;
      vertex.m_normal.y = mesh->mNormals[i].y;
      vertex.m_normal.z = mesh->mNormals[i].z;
    }

    if (mesh->HasTextureCoords(0))
    {
      vertex.m_texcoord.x = mesh->mTextureCoords[0][i].x;
      vertex.m_texcoord.y = mesh->mTextureCoords[0][i].y;
    }

    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    const aiFace& face = mesh->mFaces[i];

    for (unsigned int j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  return
  {
    .m_vertices     = vertices,
    .m_indices      = indices,
    .m_textureNames = {"models/male/textures/hero_baseColor.png"},
  };
}
}
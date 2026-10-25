//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../ImportModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "assimp-vc143-mt.lib")

namespace cge::filesystem
{
//----------------------------------------------------
// CAssimp
//----------------------------------------------------
class CAssimp final
{
public:

  TResult LoadActorFromFile(const std::filesystem::path& filename, TActorModel& model);

private:

  TMeshModel ExtractMeshModel(const aiScene* pScene, aiMesh* pMesh) const;
  void ExtractGeometry(aiMesh* pMesh, TMeshModel& model) const;
  void ExtractBones(aiMesh* pMesh, TAnimationImportContext& ctx) const;
  TVertexModel ExtractVertex(aiMesh* pMesh, const size_t vertexIndex) const;
  void ExtractWeights(aiMesh* pMesh, TMeshModel& model) const;
  void ExtractAnimations(const aiScene* pScene, const aiMesh* pMesh, TMeshModel& model) const;
  void ProcessNode(const aiScene* pScene, const aiNode* node, const glm::mat4& parentTransform, TAnimationImportContext& ctx) const;
  void SetDefaultPoseBoneTransforms(TMeshModel& model, TAnimationImportContext& ctx) const;

  glm::mat4 ToGlm(const aiMatrix4x4& m) const;
  glm::quat ToGlm(const aiQuaternion& q) const;
  glm::vec3 ToGlm(const aiVector3D& v) const;
};
}

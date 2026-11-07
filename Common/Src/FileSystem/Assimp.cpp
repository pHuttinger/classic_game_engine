//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/FileSystem/Assimp.h"

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

    TMeshModel meshModel = ExtractMeshModel(pScene, pMesh);
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

TMeshModel CAssimp::ExtractMeshModel(const aiScene* pScene, aiMesh* pMesh) const
{
  TMeshModel model;
  ExtractGeometry(pMesh, model);
  ExtractWeights(pMesh, model);

  TAnimationImportContext ctx
  {
    .m_globalInverseTransform = glm::inverse(ToGlm(pScene->mRootNode->mTransformation))
  };

  ExtractBones(pMesh, ctx);
  ProcessNodeTree(pScene, ctx);
  //ExtractAnimations(pScene, pMesh, model, ctx);
  SetDefaultPoseBoneTransforms(model, ctx);

  return model;
}

void CAssimp::ExtractGeometry(aiMesh* pMesh, TMeshModel& model) const
{
  model.m_vertices.reserve(pMesh->mNumVertices);

  for (size_t i = 0; i < pMesh->mNumVertices; i++)
  {
    TVertexModel vertex = ExtractVertex(pMesh, i);
    model.m_vertices.push_back(vertex);
  }

  for (size_t i = 0; i < pMesh->mNumFaces; i++)
  {
    const aiFace& face = pMesh->mFaces[i];
    for (size_t j = 0; j < face.mNumIndices; j++)
    {
      model.m_indices.push_back(face.mIndices[j]);
    }
  }
}

void CAssimp::ExtractBones(aiMesh* pMesh, TAnimationImportContext& ctx) const
{
  for (size_t i = 0U; i < pMesh->mNumBones; i++)
  {
    const aiBone* pBone = pMesh->mBones[i];
    const aiMatrix4x4 offsetMatrix = pBone->mOffsetMatrix;

    TBoneModel boneModel
    {
      .m_offsetMatrix = ToGlm(offsetMatrix),
    };

    std::string nodeName = pBone->mName.C_Str();
    ctx.m_boneMap[nodeName] = boneModel;
  }
}

TVertexModel CAssimp::ExtractVertex(aiMesh* pMesh, const size_t vertexIndex) const
{
  TVertexModel vertex;
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

void CAssimp::ExtractWeights(aiMesh* pMesh, TMeshModel& model) const
{
  std::unordered_map<size_t, std::vector<TWeight>> weightsPerVertex;
  for (size_t i = 0; i < pMesh->mNumBones; i++)
  {
    const aiBone* bone = pMesh->mBones[i];
    for (size_t j = 0; j < bone->mNumWeights; j++)
    {
      const size_t vertexIndex = bone->mWeights[j].mVertexId;
      const TWeight weight {i, bone->mWeights[j].mWeight};
      weightsPerVertex[vertexIndex].push_back(weight);
    }
  }

  for (auto& keyVal : weightsPerVertex)
  {
    TVertexModel& vertex = model.m_vertices[keyVal.first];
    std::vector<TWeight> weights = keyVal.second;
    for (size_t i = 0U; i < weights.size(); i++)
    {
      switch (i)
      {
        case 0U: vertex.m_boneWeights.x = weights[i].m_weight; vertex.m_boneIndices.x = weights[i].m_boneIndex; break;
        case 1U: vertex.m_boneWeights.y = weights[i].m_weight; vertex.m_boneIndices.y = weights[i].m_boneIndex; break;
        case 2U: vertex.m_boneWeights.z = weights[i].m_weight; vertex.m_boneIndices.z = weights[i].m_boneIndex; break;
        case 3U: vertex.m_boneWeights.w = weights[i].m_weight; vertex.m_boneIndices.w = weights[i].m_boneIndex; break;
      }
    }
  }
}

void CAssimp::ExtractAnimations(const aiScene* pScene, const aiMesh* pMesh, TMeshModel& model, TAnimationImportContext& ctx) const
{
  for(size_t i = 0; i < pScene->mNumAnimations; i++)
  {
    const aiAnimation* animation = pScene->mAnimations[i];
    for (size_t j = 0; j < animation->mNumChannels; j++)
    {
      const aiNodeAnim* nodeAnim = animation->mChannels[j];
    /*  for (size_t k = 0; k < nodeAnim->mNumPositionKeys; k++)
      {*/
        const aiVectorKey& positionKey = nodeAnim->mPositionKeys[8];
        const aiVectorKey& scaleKey = nodeAnim->mScalingKeys[8];
        const aiQuatKey& rotationKey = nodeAnim->mRotationKeys[8];
     /* }*/

        if (ctx.m_boneMap.find(nodeAnim->mNodeName.C_Str()) != ctx.m_boneMap.end())
        {
          TBoneModel& boneModel = ctx.m_boneMap[nodeAnim->mNodeName.C_Str()];
          boneModel.m_localTransform = 
            glm::translate(glm::mat4(1.0f), ToGlm(positionKey.mValue)) *
            glm::mat4_cast(ToGlm(rotationKey.mValue)) *
            glm::scale(glm::mat4(1.0f), ToGlm(scaleKey.mValue));
        }
    }
  }
}

void CAssimp::ProcessNode(const aiScene* pScene, const aiNode* node, const glm::mat4& parentTransform, TAnimationImportContext& ctx) const
{
  const glm::mat4 localTransform  = ToGlm(node->mTransformation);
  const glm::mat4 globalTransform = parentTransform * localTransform;

  std::string nodeName = node->mName.C_Str();
  if (ctx.m_boneMap.find(nodeName) != ctx.m_boneMap.end())
  {
    TBoneModel& boneModel = ctx.m_boneMap[nodeName];
    boneModel.m_parentTransform = parentTransform;
    boneModel.m_localTransform  = localTransform;
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i)
  {
    ProcessNode(pScene, node->mChildren[i], globalTransform, ctx);
  }
}

void CAssimp::ProcessNodeTree(const aiScene* pScene, TAnimationImportContext& ctx) const
{
  //walk through NodeTree recursive
  ProcessNode(pScene, pScene->mRootNode, glm::mat4(1.0f), ctx);
}

void CAssimp::SetDefaultPoseBoneTransforms(TMeshModel& model, TAnimationImportContext& ctx) const
{
  for (auto& kv : ctx.m_boneMap)
  {
    glm::mat4 defaultPoseMatrix    =
      ctx.m_globalInverseTransform *
      kv.second.m_parentTransform  *
      kv.second.m_localTransform   *
      kv.second.m_offsetMatrix     ;

    model.m_staticBoneTransforms.push_back(defaultPoseMatrix);
  }
}

glm::mat4 CAssimp::ToGlm(const aiMatrix4x4& m) const
{
  return
  {
    m.a1, m.b1, m.c1, m.d1,
    m.a2, m.b2, m.c2, m.d2,
    m.a3, m.b3, m.c3, m.d3,
    m.a4, m.b4, m.c4, m.d4
  };
}

glm::quat CAssimp::ToGlm(const aiQuaternion& q) const
{
  return glm::quat(q.w, q.x, q.y, q.z);
}

glm::vec3 CAssimp::ToGlm(const aiVector3D& v) const
{
  return glm::vec3(v.x, v.y, v.z);
}
}
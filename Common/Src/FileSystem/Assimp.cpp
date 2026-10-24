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

    TMeshModel meshModel = ExtractMeshModel(pMesh);
    if (pMesh->HasBones())
    {
      meshModel.m_meshType = EMeshType::Skinned;
    }

    ExtractAnimations(pScene, pMesh, meshModel);

    //TODO don't do it so
    meshModel.m_textureNames = { "models/running/texture.png" };

    model.m_meshModels.push_back(meshModel);
  }

  return TResult::Okay();
}

TMeshModel CAssimp::ExtractMeshModel(aiMesh* pMesh) const
{
  TMeshModel model;

  ExtractGeometry(pMesh, model);
  ExtractBones(pMesh, model);
  ExtractWeights(pMesh, model);

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

void CAssimp::ExtractBones(aiMesh* pMesh, TMeshModel& model) const
{
  for (size_t i = 0U; i < pMesh->mNumBones; i++)
  {
    const aiMatrix4x4 m = pMesh->mBones[i]->mOffsetMatrix;
    model.m_boneTransforms.push_back(ToGlm(m));
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
      unsigned int vertexIndex = bone->mWeights[j].mVertexId;
      float weight = bone->mWeights[j].mWeight;
      weightsPerVertex[vertexIndex].push_back({i, weight});
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

void CAssimp::ExtractAnimations(const aiScene* pScene, const aiMesh* pMesh, TMeshModel& model) const
{
  model.m_animations.resize(pScene->mNumAnimations);
  for (unsigned int a = 0; a < pScene->mNumAnimations; a++)
  {
    const aiAnimation* animation = pScene->mAnimations[a];
    TAnimation& animationModel = model.m_animations[a];
    for (unsigned int c = 0; c < animation->mNumChannels; c++)
    {
      const aiNodeAnim* channel = animation->mChannels[c];

      if (c == 0)
      {
        animationModel.m_keyFrame.resize(channel->mNumPositionKeys);

        for (unsigned int k = 0; k < channel->mNumPositionKeys; k++)
        {
          animationModel.m_keyFrame[k].m_boneTransforms.resize(model.m_boneTransforms.size());
        }
      }
    }
  }

  ProcessNode(pScene, pMesh, pScene->mRootNode, glm::mat4(1.0f), model);
}

void CAssimp::ProcessNode(const aiScene* pScene, const aiMesh* pMesh, const aiNode* node, const glm::mat4& parentTransform, TMeshModel& model) const
{
  const glm::mat4 globalInverseTransform = glm::inverse(ToGlm(pScene->mRootNode->mTransformation));
  const glm::mat4 localTransform = ToGlm(node->mTransformation);
  glm::mat4 globalTransform = parentTransform * localTransform;

  // Hier ist globalTransform die globale Transformation
  // dieses Nodes.

  for (unsigned int a = 0; a < pScene->mNumAnimations; a++)
  {
    const aiAnimation* animation = pScene->mAnimations[a];
    TAnimation& animationModel = model.m_animations[a];
    for (unsigned int c = 0; c < animation->mNumChannels; c++)
    {
      const aiNodeAnim* channel = animation->mChannels[c];
      if (channel->mNodeName != node->mName)
      {
        continue;
      }

      for (unsigned int k = 0; k < channel->mNumPositionKeys; k++)
      {
        aiVectorKey positionKey = channel->mPositionKeys[k];
        aiQuatKey   rotationKey = channel->mRotationKeys[k];
        aiVectorKey scaleKey = channel->mScalingKeys[k];

        if (k == 0)
        {
          animationModel.m_keyFrame[k].m_timeOfSnapshot = positionKey.mTime;
        }

        glm::mat4 rotationMatrix    = glm::mat4_cast(ToGlm(rotationKey.mValue));
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), ToGlm(positionKey.mValue));
        glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), ToGlm(scaleKey.mValue));

        glm::mat4 transform = translationMatrix * rotationMatrix * scaleMatrix;
        globalTransform = parentTransform * transform;

        for (size_t b = 0; b < pMesh->mNumBones; b++)
        {
          if (pMesh->mBones[b]->mName == channel->mNodeName)
          {
            animationModel.m_keyFrame[k].m_boneTransforms[b] =
              globalInverseTransform     *
              parentTransform            *
              transform                  *
              model.m_boneTransforms[b];
          }
        }
      }
    }
  }

  for (unsigned int i = 0; i < node->mNumChildren; ++i)
  {
    ProcessNode(pScene, pMesh, node->mChildren[i], globalTransform, model);
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
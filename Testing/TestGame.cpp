//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "TestGame.h"

cge::TResult CTestGame::OnCreate(cge::CInstance& instance)
{
  cge::CSceneManager& sceneManager = instance.GetSceneManager();
  cge::CAssetManager& assetManager = instance.GetAssetManager();

  cge::CScene* pScene = sceneManager.CreateScene("TestScene");
  sceneManager.SetCurrentScene("TestScene");

  std::vector<cge::render::TVertexStaticMesh> vertices =
  {
    cge::render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, {0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},

    cge::render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},

    cge::render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {0.0f,  1.0f,  0.0f}, {0.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, {0.0f,  1.0f,  0.0f}, {1.0f, 1.0f}},

    cge::render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f,  0.0f}, {1.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f}},

    cge::render::TVertexStaticMesh{{-1.0f, -1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{-1.0f,  1.0f,  1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{-1.0f,  1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{-1.0f, -1.0f, -1.0f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},

    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f, -1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f,  1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
    cge::render::TVertexStaticMesh{{ 1.0f, -1.0f,  1.0f}, { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}}
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

  cge::TStaticMeshCreateInfo staticMeshCreateInfo
  {
    .m_vertexData =
    {
      .m_size  = vertices.size() * sizeof(cge::render::TVertexStaticMesh),
      .m_pData = vertices.data(),
    },
    .m_indexData =
    {
      .m_size  = indices.size() * sizeof(uint32_t),
      .m_pData = indices.data(),
    },
    .m_indexCount = indices.size(),
  };

  cge::CStaticMesh* pStaticMesh = assetManager.CreateStaticMesh(staticMeshCreateInfo);
  
  m_pActor = assetManager.CreateActor();
  m_pActor->AddStaticMesh(pStaticMesh);
  pScene->AddActor(m_pActor);

  m_pActor2 = assetManager.CreateActor();
  m_pActor2->AddStaticMesh(pStaticMesh);
  m_pActor->AddChild(m_pActor2);

  cge::CCamera& camera = pScene->GetCurrentCamera();
  camera.GetTransform().GetPosition() = glm::vec3(0.0f, 0.0f, -5.0f);

  m_pActor2->GetTransform().GetPosition().x = 2.0f;
  m_pActor2->GetTransform().GetScale() *= 0.5f;

  return cge::TResult::Okay();
}

void CTestGame::OnTick(const float deltaTime)
{
  static float rotationAngle = 0.0f;
  static float rotationAngle2 = 0.0f;
  const float rotationSpeed = 50.0f * deltaTime;
  m_pActor->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle += rotationSpeed), glm::vec3(1.0f, 1.0f, 1.0f));
  m_pActor2->GetTransform().GetRotation() = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle2 += rotationSpeed), glm::vec3(1.0f, 1.0f, 1.0f));
}
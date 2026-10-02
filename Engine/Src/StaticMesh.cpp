//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/StaticMesh.h"

namespace cge
{
TResult CStaticMesh::Initialize(render::CRenderer& renderer, const render::TMeshCreateInfo& createInfo)
{
  CGE_TRY(renderer.GetMeshFactory().CreateMesh(createInfo, m_pMeshData));

  render::TShaderDataCreateInfo shaderDataCreateInfo
  {
    .m_size = sizeof(TStaticMeshShaderData)
  };

  m_pShaderData = std::make_unique<render::CShaderData>(renderer);
  CGE_TRY(m_pShaderData->Initialize(shaderDataCreateInfo));

  //TODO remove
  constexpr const float FOV = 60.0f;
  constexpr const float NEAR_PLANE = 0.1f;
  constexpr const float FAR_PLANE = 1000.0f;

  glm::mat4 projectionMatrix = glm::perspectiveRH_ZO(glm::radians(FOV), static_cast<float>(800) / static_cast<float>(600), NEAR_PLANE, FAR_PLANE);

  glm::mat4 rotationMatrix = glm::mat4_cast(glm::quat());

  glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
  glm::vec3 forward = glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
  glm::vec3 right = glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
  glm::vec3 up = glm::cross(forward, right);
  glm::vec3 target = position + forward;

  glm::mat4 viewMatrix = glm::lookAtRH(position, target, up);

  glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

  TStaticMeshShaderData cbData{};
  cbData.m_mvp = glm::transpose(projectionMatrix * viewMatrix * modelMatrix);
  cbData.m_model = glm::transpose(modelMatrix);

  rhi::TBufferUpdateInfo updateInfo
  {
    .m_pData = &cbData,
  };

  m_pShaderData->UpdateData(updateInfo);

  //TODO remove

  return TResult::Okay();
}
}

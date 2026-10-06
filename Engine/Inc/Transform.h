//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge
{
class CTransform
{
public:

  CTransform();
  virtual ~CTransform() = default;

  glm::vec3& GetPosition();
  glm::quat& GetRotation();
  glm::vec3& GetScale();

  glm::mat4 GetModelMatrix();

private:

  glm::vec3 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
}

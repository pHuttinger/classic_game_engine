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

  glm::vec3& GetPosition() { return m_position; };
  glm::quat& GetRotation() { return m_rotation; };
  glm::vec3& GetScale()    { return m_scale;    };

  const glm::vec3& GetPositionConst() const { return m_position; };
  const glm::quat& GetRotationConst() const { return m_rotation; };
  const glm::vec3& GetScaleConst()    const { return m_scale;    };

  glm::mat4 GetModelMatrix();

private:

  glm::vec3 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
}

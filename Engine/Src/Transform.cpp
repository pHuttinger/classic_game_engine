//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Transform.h"

namespace cge
{
CTransform::CTransform()
  : m_position(0.0f)
  , m_rotation(glm::identity<glm::quat>())
  , m_scale(1.0f)
{
}

glm::mat4 CTransform::GetModelMatrix()
{
  glm::mat4 rotationMatrix    = glm::mat4_cast(GetRotation());
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), GetPosition());
  glm::mat4 scaleMatrix       = glm::scale(glm::mat4(1.0f), GetScale());

  return translationMatrix * rotationMatrix * scaleMatrix;
}
}

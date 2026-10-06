//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Transform.h"

namespace cge
{
constexpr float DEFAULT_FRUSTUM_CULLING_RADIUS = 10.0f;

//------------------------------------------------
// TFrustumPlane
//------------------------------------------------
struct TFrustumPlane final
{
  glm::vec3 m_normal;
  float m_distance;
};

//------------------------------------------------
// TFrustum
//------------------------------------------------
struct TFrustum final
{
  TFrustumPlane m_planes[6];
};

//------------------------------------------------
// CCamera
//------------------------------------------------
class CCamera
{
public:

  CCamera(const glm::vec2& viewportSize);
  virtual ~CCamera() = default;

  void Update();

  CTransform& GetTransform();

  const glm::mat4 GetViewMatrix() const;
  const glm::mat4 GetProjectionMatrix() const;

  bool SphereInFrustum(const glm::vec3& center, float radius) const;

private:

  TFrustum ExtractFrustum() const;

  glm::vec2  m_viewportSize;
  glm::mat4  m_viewMatrix;
  glm::mat4  m_projectionMatrix;
  CTransform m_transform;
};
}
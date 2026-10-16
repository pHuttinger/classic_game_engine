//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "DrawItem.h"
#include "ShaderData.h"

namespace cge::render
{
//----------------------------------------------------
// TDrawCall
//----------------------------------------------------
struct TDrawCall final
{
  CDrawItem*                m_pDrawItem = nullptr;
  std::vector<CShaderData*> m_shaderData;
};

//----------------------------------------------------
// CFrameInput
//----------------------------------------------------
class CFrameInput final
{
friend class CRenderer;
friend class CGeometryPass;

public:

  CFrameInput();

  void Reset();
  void AddDrawCall(const TDrawCall& drawCall);
  void SetCameraPosition(const glm::vec3& position);

private:

  glm::vec4              m_clearColor;
  glm::vec3              m_lightDirection;
  glm::vec3              m_cameraPosition;
  std::vector<TDrawCall> m_drawCalls;
};
}
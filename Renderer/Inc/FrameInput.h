//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Mesh.h"
#include "ShaderData.h"

namespace cge::render
{
//----------------------------------------------------
// TDrawCall
//----------------------------------------------------
struct TDrawCall final
{
  CMeshData* m_pMeshData = nullptr;
  std::vector<CShaderData*> m_shaderData;
};

//----------------------------------------------------
// CFrameInput
//----------------------------------------------------
class CFrameInput final
{
public:

  CFrameInput();

  void Reset();
  void AddDrawCall(const TDrawCall& drawCall);

  glm::vec4 GetClearColor() const { return m_clearColor; }
  const std::vector<TDrawCall>& GetDrawCalls() const { return m_drawCalls; }

private:

  glm::vec4 m_clearColor;
  std::vector<TDrawCall> m_drawCalls;
};
}
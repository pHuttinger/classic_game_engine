//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>

namespace cge
{
//----------------------------------------------------
// TStaticMeshShaderData
//----------------------------------------------------
struct TStaticMeshShaderData final
{
  glm::mat4 m_mvp;
};

//----------------------------------------------------
// CStaticMesh
//----------------------------------------------------
class CStaticMesh
{
public:

  TResult Initialize(render::CRenderer& renderer, const render::TMeshCreateInfo& createInfo);

  render::CMeshData* GetMeshData() const { return m_pMeshData.get(); };
  render::CShaderData* GetShaderData() const { return m_pShaderData.get(); }

private:

  std::unique_ptr<render::CMeshData> m_pMeshData;
  std::unique_ptr<render::CShaderData> m_pShaderData;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Mesh.h"
#include "../Inc/Renderer.h"

namespace cge::render
{
CMesh::CMesh(const TMeshCreateInfo& createInfo)
  : m_createInfo(createInfo)
{
}

CMeshFactory::CMeshFactory(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CMeshFactory::CreateMesh(const TMeshCreateInfo& createInfo, std::unique_ptr<CMesh>& pMesh)
{
  pMesh = std::make_unique<CMesh>(createInfo);

  TSharedMeshResources resources;

  CResourceManager& resourceManager = m_renderer.GetResourceManager();
  CGE_TRY(resourceManager.GetSampler(resources.m_pSampler));
  CGE_TRY(resourceManager.GetVertexShader(createInfo.m_vertexShaderName, resources.m_pVertexShader));
  CGE_TRY(resourceManager.GetPixelShader(createInfo.m_pixelShaderName, resources.m_pPixelShader));
  CGE_TRY(resourceManager.GetVertexDescriptor(createInfo.m_vertexType, resources.m_pVertexShader.get(), resources.m_pVertexDescriptor));
  CGE_TRY(resourceManager.GetTexture(createInfo.m_textureName, resources.m_pTexture));

  pMesh->m_sharedResources = resources;

  return TResult::Okay();
}
}

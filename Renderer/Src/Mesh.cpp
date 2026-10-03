//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Mesh.h"
#include "../Inc/Renderer.h"

namespace cge::render
{
CMeshData::CMeshData(const TMeshCreateInfo& createInfo)
  : m_createInfo(createInfo)
{
}

CMeshFactory::CMeshFactory(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CMeshFactory::CreateMesh(const TMeshCreateInfo& createInfo, std::unique_ptr<CMeshData>& pMeshData)
{
  pMeshData = std::make_unique<CMeshData>(createInfo);

  CGE_TRY(CreateSharedMeshResources(createInfo, pMeshData->m_sharedResources));
  CGE_TRY(CreateGeometryBuffer(createInfo, pMeshData->m_geometryBuffer));

  return TResult::Okay();
}

TResult CMeshFactory::CreateSharedMeshResources(const TMeshCreateInfo& createInfo, TSharedMeshResources& sharedResources)
{
  TSharedMeshResources resources;

  CResourceManager& resourceManager = m_renderer.GetResourceManager();
  CGE_TRY(resourceManager.GetVertexShader(createInfo.m_vertexShaderName, resources.m_pVertexShader));
  CGE_TRY(resourceManager.GetPixelShader(createInfo.m_pixelShaderName, resources.m_pPixelShader));
  CGE_TRY(resourceManager.GetVertexDescriptor(createInfo.m_vertexType, createInfo.m_vertexShaderName, resources.m_pVertexDescriptor));
  CGE_TRY(resourceManager.GetTexture(createInfo.m_textureName, resources.m_pTexture));
  CGE_TRY(resourceManager.GetRasterizerState(createInfo.m_rasterizerState, resources.m_pRasterizerState));

  sharedResources = resources;

  return TResult::Okay();
}

TResult CMeshFactory::CreateGeometryBuffer(const TMeshCreateInfo& createInfo, TGeometryBuffer& geometryBuffer)
{
  CBackend& backend = m_renderer.GetBackend();

  rhi::TBufferCreateInfo vertexBufferCreateInfo
  {
    .m_usage      = rhi::EBufferUsage::Default,
    .m_bufferType = rhi::EBufferType::VertexBuffer,
    .m_size       = createInfo.m_vertexData.m_size,
    .m_pData      = createInfo.m_vertexData.m_pData,
    .m_stride     = createInfo.m_stride,
  };

  rhi::TBufferCreateInfo indexBufferCreateInfo
  {
    .m_usage      = rhi::EBufferUsage::Default,
    .m_bufferType = rhi::EBufferType::IndexBuffer,
    .m_size       = createInfo.m_indexData.m_size,
    .m_pData      = createInfo.m_indexData.m_pData,
  };

  CGE_TRY(backend.GetInstance().CreateBuffer(vertexBufferCreateInfo, geometryBuffer.m_pVertexBuffer));
  CGE_TRY(backend.GetInstance().CreateBuffer(indexBufferCreateInfo, geometryBuffer.m_pIndexBuffer));

  return TResult::Okay();
}
}

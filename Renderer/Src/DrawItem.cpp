//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/DrawItem.h"
#include "../Inc/Renderer.h"

namespace cge::render
{
CDrawItem::CDrawItem(CRenderer& renderer, const TDrawItemCreateInfo& createInfo)
  : m_renderer(renderer)
  , m_createInfo(createInfo)
{
}

TResult CDrawItem::SetRasterizerState(const ERasterizerState state)
{
  CResourceManager& resourceManager = m_renderer.GetResourceManager();

  CGE_TRY(resourceManager.GetRasterizerState(state, m_sharedResources.m_pRasterizerState));

  return TResult::Okay();
}

const std::vector<rhi::ITexture*> CDrawItem::GetTextures() const
{
  std::vector<rhi::ITexture*> textures;
  for (auto& pTexture : m_sharedResources.m_pTextures)
  {
    textures.push_back(pTexture.get());
  }

  return textures;
}

CDrawItemFactory::CDrawItemFactory(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CDrawItemFactory::CreateDrawItem(const TDrawItemCreateInfo& createInfo, std::unique_ptr<CDrawItem>& pMeshData)
{
  pMeshData = std::make_unique<CDrawItem>(m_renderer, createInfo);

  CGE_TRY(CreateSharedDrawResources(createInfo, pMeshData->m_sharedResources));
  CGE_TRY(CreateGeometryBuffer(createInfo, pMeshData->m_geometryBuffer));

  return TResult::Okay();
}

TResult CDrawItemFactory::CreateSharedDrawResources(const TDrawItemCreateInfo& createInfo, TSharedDrawResources& sharedResources)
{
  TSharedDrawResources resources;

  CResourceManager& resourceManager = m_renderer.GetResourceManager();
  CGE_TRY(resourceManager.GetVertexShader    (createInfo.m_vertexShaderName, resources.m_pVertexShader));
  CGE_TRY(resourceManager.GetPixelShader     (createInfo.m_pixelShaderName, resources.m_pPixelShader));
  CGE_TRY(resourceManager.GetVertexDescriptor(createInfo.m_vertexType, createInfo.m_vertexShaderName, resources.m_pVertexDescriptor));
  CGE_TRY(resourceManager.GetRasterizerState (createInfo.m_rasterizerState, resources.m_pRasterizerState));
  
  for (auto& textureName : createInfo.m_textureNames)
  {
    std::shared_ptr<rhi::ITexture> pTexture;
    CGE_TRY(resourceManager.GetTexture(textureName, pTexture));
    resources.m_pTextures.push_back(pTexture);
  }

  sharedResources = resources;

  return TResult::Okay();
}

TResult CDrawItemFactory::CreateGeometryBuffer(const TDrawItemCreateInfo& createInfo, TGeometryBuffer& geometryBuffer)
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

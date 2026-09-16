//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/ResourceManager.h"

namespace cge::render
{
CResourceManager::CResourceManager(CBackend& backend)
  : m_backend(backend)
{
}

TResult CResourceManager::GetSampler(std::shared_ptr<rhi::ISampler> pSampler)
{
  if (m_pSampler == nullptr)
  {
    std::unique_ptr<rhi::ISampler> sampler;
    if (TResult result = m_backend.GetInstance().CreateSampler(sampler); result.IsError())
    {
      return result;
    }

    m_pSampler = std::move(sampler);
  }

  pSampler = m_pSampler;
  return TResult::Okay();
}

TResult CResourceManager::GetVertexDescriptor(const EVertexType vertexType, rhi::IVertexShader* pVertexShader, std::shared_ptr<rhi::IVertexDescriptor> pVertexDescriptor)
{
  if (m_vertexDescriptors.find(vertexType) == m_vertexDescriptors.end())
  {
    rhi::TVertexDescriptorCreateInfo createInfo
    {
      .m_pVertexShader = pVertexShader,
      .m_vertexAttributeInfos = GetVertexAttributesByVertexType(vertexType)
    };

    std::unique_ptr<rhi::IVertexDescriptor> pVertexDescriptor;
    if (TResult result = m_backend.GetInstance().CreateVertexDescriptor(createInfo, pVertexDescriptor); result.IsError())
    {
      return result;
    }

    m_vertexDescriptors[vertexType] = std::move(pVertexDescriptor);
  }

  pVertexDescriptor = m_vertexDescriptors[vertexType];
  return TResult::Okay();
}

TResult CResourceManager::GetVertexShader(const std::string& shaderName, std::shared_ptr<rhi::IVertexShader> pVertexShader)
{
  if (m_vertexShaders.find(shaderName) == m_vertexShaders.end())
  {
    rhi::TVertexShaderCreateInfo createInfo
    {
      .m_shaderName = shaderName
    };

    std::unique_ptr<rhi::IVertexShader> pVertexShader;
    if (TResult result = m_backend.GetInstance().CreateVertexShader(createInfo, pVertexShader); result.IsError())
    {
      return result;
    }

    m_vertexShaders[shaderName] = std::move(pVertexShader);
  }

  pVertexShader = m_vertexShaders[shaderName];
  return TResult::Okay();
}

TResult CResourceManager::GetPixelShader(const std::string& shaderName, std::shared_ptr<rhi::IPixelShader> pPixelShader)
{
  if (m_pixelShaders.find(shaderName) == m_pixelShaders.end())
  {
    rhi::TPixelShaderCreateInfo createInfo
    {
      .m_shaderName = shaderName
    };

    std::unique_ptr<rhi::IPixelShader> pVertexShader;
    if (TResult result = m_backend.GetInstance().CreatePixelShader(createInfo, pVertexShader); result.IsError())
    {
      return result;
    }

    m_pixelShaders[shaderName] = std::move(pVertexShader);
  }

  pPixelShader = m_pixelShaders[shaderName];
  return TResult::Okay();
}

TResult CResourceManager::GetTexture(const std::string& textureName, std::shared_ptr<rhi::ITexture> pTexture)
{
  if (m_textures.find(textureName) == m_textures.end())
  {
    rhi::TTextureCreateInfo createInfo
    {
      .m_filename = textureName
    };

    std::unique_ptr<rhi::ITexture> pTexture;
    if (TResult result = m_backend.GetInstance().CreateTexture(createInfo, pTexture); result.IsError())
    {
      return result;
    }

    m_textures[textureName] = std::move(pTexture);
  }

  pTexture = m_textures[textureName];
  return TResult::Okay();
}

std::vector<rhi::TVertexAttribute> CResourceManager::GetVertexAttributesByVertexType(const EVertexType vertexType) const
{
  switch (vertexType)
  {
    case EVertexType::PositionNormalTexcoord:
    return
    {
      {rhi::EVertexAttributeUsage::Position, rhi::EVertexAttributeFormat::Float3},
      //TODO add type for Normal {rhi::EVertexAttributeUsage::No, rhi::EVertexAttributeFormat::Float2},
      {rhi::EVertexAttributeUsage::Texcoord, rhi::EVertexAttributeFormat::Float2},
    };
  }

  return {};
}
}
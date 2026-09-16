//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "Common.h"

namespace cge::render
{
class CResourceManager final
{
public:

  CResourceManager(CBackend& backend);

  TResult GetSampler(std::shared_ptr<rhi::ISampler> pSampler);
  TResult GetVertexDescriptor(const EVertexType vertexType, rhi::IVertexShader* pVertexShader, std::shared_ptr<rhi::IVertexDescriptor> pVertexDescriptor);
  TResult GetVertexShader(const std::string& shaderName, std::shared_ptr<rhi::IVertexShader> pVertexShader);
  TResult GetPixelShader(const std::string& shaderName, std::shared_ptr<rhi::IPixelShader> pVixelShader);
  TResult GetTexture(const std::string& textureName, std::shared_ptr<rhi::ITexture> pTexture);

private:

  std::vector<rhi::TVertexAttributeInfo> GetVertexAttributeInfosByVertexType(const EVertexType vertexType) const;

  CBackend& m_backend;

  std::shared_ptr<rhi::ISampler> m_pSampler;
  std::unordered_map<EVertexType, std::shared_ptr<rhi::IVertexDescriptor>> m_vertexDescriptors;
  std::unordered_map<std::string, std::shared_ptr<rhi::IVertexShader>> m_vertexShaders;
  std::unordered_map<std::string, std::shared_ptr<rhi::IPixelShader>> m_pixelShaders;
  std::unordered_map<std::string, std::shared_ptr<rhi::ITexture>> m_textures;
};
}
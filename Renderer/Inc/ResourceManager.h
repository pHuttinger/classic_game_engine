//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "Common.h"
#include "ShaderData.h"

namespace cge::render
{
class CResourceManager final
{
public:

  CResourceManager(CBackend& backend);

  TResult GetSampler(std::shared_ptr<rhi::ISampler>& pSampler);
  TResult GetVertexDescriptor(const EVertexType vertexType, const std::string& vertexShaderName, std::shared_ptr<rhi::IVertexDescriptor>& pVertexDescriptor);
  TResult GetVertexShader(const std::string& shaderName, std::shared_ptr<rhi::IVertexShader>& pVertexShader);
  TResult GetPixelShader(const std::string& shaderName, std::shared_ptr<rhi::IPixelShader>& pVixelShader);
  TResult GetTexture(const std::string& textureName, std::shared_ptr<rhi::ITexture>& pTexture);
  TResult GetRasterizerState(const ERasterizerState rasterizerState, std::shared_ptr<rhi::IRasterizerState>& pRasterizerState);
  TResult GetConstantBuffer(const TShaderDataCreateInfo& createInfo, std::shared_ptr<rhi::IBuffer>& pBuffer);

private:

  std::vector<rhi::TVertexAttribute> GetVertexAttributesByVertexType(const EVertexType vertexType) const;
  rhi::TRasterizerStateCreateInfo GetRasterizerStateCreateInfo(const ERasterizerState rasterizerState) const;
  std::string GetShaderDataCreateInfoKey(const TShaderDataCreateInfo& createInfo) const;

  CBackend& m_backend;

  std::shared_ptr<rhi::ISampler> m_pSampler;
  std::unordered_map<EVertexType, std::shared_ptr<rhi::IVertexDescriptor>> m_vertexDescriptors;
  std::unordered_map<std::string, std::shared_ptr<rhi::IVertexShader>> m_vertexShaders;
  std::unordered_map<std::string, std::shared_ptr<rhi::IPixelShader>> m_pixelShaders;
  std::unordered_map<std::string, std::shared_ptr<rhi::ITexture>> m_textures;
  std::unordered_map<ERasterizerState, std::shared_ptr<rhi::IRasterizerState>> m_rasterizerStates;
  std::unordered_map<std::string, std::shared_ptr<rhi::IBuffer>> m_constantBuffers;
};
}
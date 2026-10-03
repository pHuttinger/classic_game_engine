//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "Common.h"

namespace cge::render
{
class CRenderer;

//----------------------------------------------------
// TMeshCreateInfo
//----------------------------------------------------
struct TMeshCreateInfo final
{
  EVertexType      m_vertexType      = EVertexType::Undefined;
  std::string      m_vertexShaderName;
  std::string      m_pixelShaderName;
  std::string      m_textureName;    //TODO this should'nt be done like this
  TDataHandle      m_vertexData;
  TDataHandle      m_indexData;
  uint32_t         m_indexCount      = 0U;
  size_t           m_stride          = 0U;
  ERasterizerState m_rasterizerState = ERasterizerState::Solid; //TODO this should'nt be done like this
};

//----------------------------------------------------
// TSharedMeshResources
//----------------------------------------------------
struct TSharedMeshResources final
{
  std::shared_ptr<rhi::IVertexShader>     m_pVertexShader;
  std::shared_ptr<rhi::IPixelShader>      m_pPixelShader;
  std::shared_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::shared_ptr<rhi::ITexture>          m_pTexture;
  std::shared_ptr<rhi::IRasterizerState>  m_pRasterizerState;
};

//----------------------------------------------------
// TGeometryBuffer
//----------------------------------------------------
struct TGeometryBuffer final
{
  std::unique_ptr<rhi::IBuffer> m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer> m_pIndexBuffer;
};

//----------------------------------------------------
// CMeshData
//----------------------------------------------------
class CMeshData final
{
friend class CMeshFactory;

public:

  CMeshData(const TMeshCreateInfo& createInfo);

  TMeshCreateInfo& GetCreateInfo() { return m_createInfo; }
  TGeometryBuffer& GetGeometryBuffer() { return m_geometryBuffer; }
  TSharedMeshResources& GetSharedMeshResources() { return m_sharedResources; }

private:

  TMeshCreateInfo      m_createInfo;
  TGeometryBuffer      m_geometryBuffer;
  TSharedMeshResources m_sharedResources;
};

//----------------------------------------------------
// 
// CMeshFactory
//----------------------------------------------------
class CMeshFactory final
{
public:

  CMeshFactory(CRenderer& renderer);

  TResult CreateMesh(const TMeshCreateInfo& createInfo, std::unique_ptr<CMeshData>& pMeshData);

private:

  TResult CreateSharedMeshResources(const TMeshCreateInfo& createInfo, TSharedMeshResources& sharedResources);
  TResult CreateGeometryBuffer(const TMeshCreateInfo& createInfo, TGeometryBuffer& geometryBuffer);

  CRenderer& m_renderer;
};
}
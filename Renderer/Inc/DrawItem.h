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
// TDrawItemCreateInfo
//----------------------------------------------------
struct TDrawItemCreateInfo final
{
  EVertexType      m_vertexType      = EVertexType::Undefined;
  std::string      m_vertexShaderName;
  std::string      m_pixelShaderName;
  std::string      m_textureName;
  TDataHandle      m_vertexData;
  TDataHandle      m_indexData;
  size_t           m_indexCount      = 0U;
  size_t           m_stride          = 0U;
  ERasterizerState m_rasterizerState = ERasterizerState::Solid; //TODO this should'nt be done like this
};

//----------------------------------------------------
// TSharedDrawResources
//----------------------------------------------------
struct TSharedDrawResources final
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
// CDrawItem
//----------------------------------------------------
class CDrawItem final
{
friend class CDrawItemFactory;

public:

  CDrawItem(CRenderer& renderer, const TDrawItemCreateInfo& createInfo);

  TResult SetRasterizerState(const ERasterizerState state);

  TDrawItemCreateInfo&  GetCreateInfo()          { return m_createInfo;      }
  TGeometryBuffer&      GetGeometryBuffer()      { return m_geometryBuffer;  }
  TSharedDrawResources& GetSharedMeshResources() { return m_sharedResources; }

private:

  CRenderer&           m_renderer;
  TDrawItemCreateInfo  m_createInfo;
  TGeometryBuffer      m_geometryBuffer;
  TSharedDrawResources m_sharedResources;
};

//----------------------------------------------------
// CDrawItemFactory
//----------------------------------------------------
class CDrawItemFactory final
{
public:

  CDrawItemFactory(CRenderer& renderer);

  TResult CreateDrawItem(const TDrawItemCreateInfo& createInfo, std::unique_ptr<CDrawItem>& pMeshData);

private:

  TResult CreateSharedDrawResources(const TDrawItemCreateInfo& createInfo, TSharedDrawResources& sharedResources);
  TResult CreateGeometryBuffer(const TDrawItemCreateInfo& createInfo, TGeometryBuffer& geometryBuffer);

  CRenderer& m_renderer;
};
}
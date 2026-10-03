//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderGraph.h"

namespace cge::render
{
//----------------------------------------------------
// TComposerRenderResources
//----------------------------------------------------
struct TComposerRenderResources final
{
  std::unique_ptr<rhi::IVertexShader>     m_pVertexShader;
  std::unique_ptr<rhi::IPixelShader>      m_pPixelShader;
  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer>           m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer>           m_pIndexBuffer;
  std::unique_ptr<rhi::ISampler>          m_pSampler;
  std::unique_ptr<rhi::IRasterizerState>  m_pRasterizerState;
};

//----------------------------------------------------
// TComposerVertex
//----------------------------------------------------
struct TComposerVertex final
{
  glm::vec2 m_position;
  glm::vec2 m_texcoord;
};

//----------------------------------------------------
// CComposer
//----------------------------------------------------
class CComposer final
{
public:

  CComposer(CBackend& backend);

  TResult Initialize();

  void MergeAndRender(std::vector<rhi::IRenderTarget*>& renderGraphOutput);

private:

  TResult CreateVertexShader();
  TResult CreatePixelShader();
  TResult CreateVertexDescriptor();
  TResult CreateVertexBuffer();
  TResult CreateIndexBuffer();
  TResult CreateSampler();
  TResult CreateRasterizerState();

  CBackend& m_backend;
  TComposerRenderResources m_renderResources;
};
}
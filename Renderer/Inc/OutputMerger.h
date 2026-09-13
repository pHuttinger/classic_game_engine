//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderGraph.h"

namespace cge::render
{
//----------------------------------------------------
// TOutputMergerRenderResources
//----------------------------------------------------
struct TOutputMergerRenderResources final
{
  std::unique_ptr<rhi::IVertexShader>     m_pVertexShader;
  std::unique_ptr<rhi::IPixelShader>      m_pPixelShader;
  std::unique_ptr<rhi::IVertexDescriptor> m_pVertexDescriptor;
  std::unique_ptr<rhi::IBuffer>           m_pVertexBuffer;
  std::unique_ptr<rhi::IBuffer>           m_pIndexBuffer;
  std::unique_ptr<rhi::ISampler>          m_pSampler;
};

//----------------------------------------------------
// TOutputMergerVertex TODO: switch to GLM
//----------------------------------------------------
struct TOutputMergerVertex final
{
  float x, y, z;
  float u, v;
};

//----------------------------------------------------
// COutputMerger
//----------------------------------------------------
class COutputMerger final
{
public:

  COutputMerger(CBackend& backend);

  TResult Initialize();

  void MergeAndRender(std::vector<rhi::IRenderTarget*>& renderGraphOutput);

private:

  TResult CreateVertexShader();
  TResult CreatePixelShader();
  TResult CreateVertexDescriptor();
  TResult CreateVertexBuffer();
  TResult CreateIndexBuffer();
  TResult CreateSampler();

  CBackend& m_backend;
  TOutputMergerRenderResources m_renderResources;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"

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
};

//----------------------------------------------------
// COutputMerger
//----------------------------------------------------
class COutputMerger final
{
public:

  COutputMerger(CBackend& backend);

  TResult Initialize();

  void MergeRenderTargets(const std::unordered_map<std::string, rhi::IRenderTarget*>& renderTargets);

private:

  CBackend& m_backend;
  TOutputMergerRenderResources m_renderResources;
};
}
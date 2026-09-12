//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/OutputMerger.h"

namespace cge::render
{
COutputMerger::COutputMerger(CBackend& backend)
  : m_backend(backend)
{
}

TResult COutputMerger::Initialize()
{
  CGE_TRY(m_backend.GetInstance().CreateVertexShader({ "./VS_RenderTarget.cso" }, m_renderResources.m_pVertexShader));
  CGE_TRY(m_backend.GetInstance().CreatePixelShader({ "./PS_RenderTarget.cso" }, m_renderResources.m_pPixelShader));

  return TResult::Okay();
}

void COutputMerger::MergeRenderTargets(const std::unordered_map<std::string, rhi::IRenderTarget*>& renderTargets)
{
  rhi::IRenderTarget* pAlbedoRenderTarget = renderTargets.at("Albedo");
}
}
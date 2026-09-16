//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Backend.h"
#include "RenderGraph.h"
#include "OutputMerger.h"
#include "ResourceManager.h"
#include "Mesh.h"

namespace cge::render
{
class CRenderer final
{
public:

  CRenderer();

  TResult Initialize(const rhi::TCreateInfo& createInfo);
  void RenderFrame(const CFrameInput& input);

  CBackend& GetBackend() { return m_backend; }
  CResourceManager& GetResourceManager() { return m_resourceManager; }
  CMeshFactory& GetMeshFactory() { return m_meshFactory; }

private:

  CBackend         m_backend;
  CRenderGraph     m_renderGraph;
  COutputMerger    m_outputMerger;
  CResourceManager m_resourceManager;
  CMeshFactory     m_meshFactory;
};
}
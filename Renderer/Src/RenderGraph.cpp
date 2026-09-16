//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/RenderGraph.h"
#include "../Inc/GeometryPass.h"

namespace cge::render
{
CRenderGraph::CRenderGraph(CRenderer& renderer)
  : m_renderer(renderer)
{
}

TResult CRenderGraph::Initialize()
{
  CGE_TRY(CreateGeometryPass());

  return TResult::Okay();
}

std::vector<rhi::IRenderTarget*> CRenderGraph::Execute(const CFrameInput& input) const
{
  std::vector<rhi::IRenderTarget*> output;

  for (auto& renderPass : m_renderPasses)
  {
    std::vector<rhi::IRenderTarget*> renderPassOutput = renderPass->Execute(input);
    output.insert(output.end(), renderPassOutput.begin(), renderPassOutput.end());
  }

  return output;
}

TResult CRenderGraph::CreateGeometryPass()
{
  auto geometryPass = std::make_unique<CGeometryPass>(m_renderer);

  CGE_TRY(geometryPass->Initialize());

  m_renderPasses.push_back(std::move(geometryPass));

  return TResult::Okay();
}
}
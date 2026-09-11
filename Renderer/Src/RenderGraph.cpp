//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/RenderGraph.h"
#include "../Inc/GeometryPass.h"

namespace cge::render
{
CRenderGraph::CRenderGraph(CBackend& backend)
  : m_backend(backend)
{
}

TResult CRenderGraph::Initialize()
{
  CGE_TRY(CreateGeometryPass());

  return TResult::Okay();
}

std::unordered_map<std::string, rhi::IRenderTarget*> CRenderGraph::Execute(const CFrameInput& input) const
{
  std::unordered_map<std::string, rhi::IRenderTarget*> renderTargets;

  for (auto& renderPass : m_renderPasses)
  {
    auto passRenderTargets = renderPass->Execute(input);
    for (const auto& kvp : passRenderTargets)
    {
      renderTargets[kvp.first] = kvp.second;
    }
  }

  return renderTargets;
}

TResult CRenderGraph::CreateGeometryPass()
{
  auto geometryPass = std::make_unique<CGeometryPass>(m_backend);

  if (auto result = geometryPass->Initialize(); result.IsError())
  {
    return result;
  }

  m_renderPasses.push_back(std::move(geometryPass));

  return TResult::Okay();
}
}
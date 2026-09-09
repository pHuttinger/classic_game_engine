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

void CRenderGraph::Execute(const CFrameInput& input) const
{
  for (auto& renderPass : m_renderPasses)
  {
    renderPass->Execute(input);
  }
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
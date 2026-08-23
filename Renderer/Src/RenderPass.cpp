//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/RenderPass.h"

namespace cge::render
{
CGeometryPass::CGeometryPass(rhi::IInstance& backend)
  : m_backend(backend)
{
}

void CGeometryPass::Execute(const CFrameInput& input) const
{
}
}
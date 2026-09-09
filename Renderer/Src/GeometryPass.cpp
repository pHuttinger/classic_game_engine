//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/GeometryPass.h"

namespace cge::render
{
CGeometryPass::CGeometryPass(CBackend& backend)
  : m_backend(backend)
{
}

TResult CGeometryPass::Initialize()
{
  return TResult::Okay();
}

void CGeometryPass::Execute(const CFrameInput& input) const
{
}
}
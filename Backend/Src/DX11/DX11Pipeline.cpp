//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Pipeline.h"

namespace cge::rhi::dx11
{
CPipeline::CPipeline(IInstance& instance)
  : m_instance(dynamic_cast<CInstance&>(instance))
{
}

void CPipeline::Clear()
{
}

void CPipeline::Present()
{
  m_instance.GetSwapChain()->Present(0, 0);
}
}
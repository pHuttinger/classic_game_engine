//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Backend.h"

namespace cge::render
{
TResult CBackend::Create(const rhi::TCreateInfo& createInfo)
{
  return rhi::CreateInstance(createInfo, m_pInstance);
}
}

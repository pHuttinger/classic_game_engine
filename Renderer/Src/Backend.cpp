//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Backend.h"

namespace cge::render
{
TResult CBackend::Create(const rhi::TCreateInfo& createInfo)
{
  CGE_TRY(rhi::CreateInstance(createInfo, m_pInstance));

  m_pPipeline = m_pInstance->CreatePipeline();

  return TResult::Okay();
}
}

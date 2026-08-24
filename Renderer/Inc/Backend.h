//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>
#include <Backend/Inc/Pipeline.h>

namespace cge::render
{
class CBackend final
{
public:

  CBackend() = default;
  ~CBackend() = default;

  TResult Create(const rhi::TCreateInfo& createInfo); 

  rhi::IPipeline& GetPipeline() { return *m_pPipeline; }

private:

  std::unique_ptr<rhi::IInstance> m_pInstance = nullptr;
  std::unique_ptr<rhi::IPipeline> m_pPipeline = nullptr;
};
}
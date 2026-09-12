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

  rhi::IInstance& GetInstance() { return *m_pInstance; }
  rhi::ISurface& GetSurface() { return *m_pSurface; }
  rhi::IPipeline& GetPipeline() { return *m_pPipeline; }

private:

  std::unique_ptr<rhi::IInstance> m_pInstance;
  std::unique_ptr<rhi::ISurface>  m_pSurface;
  std::unique_ptr<rhi::IPipeline> m_pPipeline;
};
}
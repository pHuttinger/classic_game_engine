//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>

namespace cge::render
{
class CBackend final
{
public:

  CBackend() = default;
  ~CBackend() = default;

  TResult Create(const rhi::TCreateInfo& createInfo); 

private:

  std::unique_ptr<rhi::IInstance> m_pInstance = nullptr;
};
}
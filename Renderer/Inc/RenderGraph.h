//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>
#include "RenderPass.h"

namespace cge::render
{
class CRenderGraph final
{
public:

  void Create(rhi::IInstance* pBackend);
  void Execute(const CFrameInput& input) const;

private:

  rhi::IInstance* m_pBackend = nullptr;
  std::vector<std::unique_ptr<IRenderPass>> m_renderPasses;
};
}
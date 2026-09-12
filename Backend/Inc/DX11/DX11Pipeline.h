//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Pipeline.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CPipeline final : public IPipeline
{
public:

  CPipeline(IInstance& instance);

  void Present() override;
  void BindRenderTargets(const std::vector<IRenderTarget*>& renderTargets, IDepthBuffer* depthBuffer) override;
  void BindShaderResources(const std::vector<IRenderTarget*>& renderTargets) override;

private:

  CInstance& m_instance;
};
}
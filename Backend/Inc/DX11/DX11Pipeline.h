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
  void SetVertexTopology(EVertexTopology topology) override;
  void BindRenderTargets(const std::vector<IRenderTarget*>& renderTargets, IDepthBuffer* depthBuffer) override;
  void BindVertexShader(IVertexShader* vertexShader) override;
  void BindPixelShader(IPixelShader* pixelShader) override;
  void BindShaderResources(const std::vector<IRenderTarget*>& renderTargets) override;
  void BindSampler(ISampler* sampler) override;
  void BindVertexDescriptor(IVertexDescriptor* vertexDescriptor) override;
  void BindVertexBuffer(IBuffer* vertexBuffer) override;
  void BindIndexBuffer(IBuffer* indexBuffer) override;
  void UpdateBufferData(IBuffer* buffer, const TDataHandle& dataHandle) override;
  void DrawIndexed(uint32_t indexCount) override;

private:

  CInstance& m_instance;
};
}
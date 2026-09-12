//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "RenderTarget.h"
#include "DepthBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexDescriptor.h"
#include "Buffer.h"

namespace cge::rhi
{
class IPipeline
{
public:

  virtual ~IPipeline() = default;

  virtual void Present() = 0;
  virtual void BindRenderTargets(const std::vector<IRenderTarget*>& renderTargets, IDepthBuffer* depthBuffer) = 0;
  virtual void BindVertexShader(IVertexShader* vertexShader) = 0;
  virtual void BindPixelShader(IPixelShader* pixelShader) = 0;
  virtual void BindShaderResources(const std::vector<IRenderTarget*>& renderTargets) = 0;
  virtual void BindSampler(ISampler* sampler) = 0;
  virtual void BindVertexDescriptor(IVertexDescriptor* vertexDescriptor) = 0;
  virtual void BindVertexBuffer(IBuffer* vertexBuffer) = 0;
  virtual void BindIndexBuffer(IBuffer* indexBuffer) = 0;
  virtual void DrawIndexed(uint32_t indexCount) = 0;
};
}
//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "RenderPass.h"
#include <Backend/Inc/RenderTarget.h>
#include <Backend/Inc/DepthBuffer.h>

namespace cge::render
{
class CGeometryPass final : public IRenderPass
{
public:

  CGeometryPass(CBackend& backend);

  TResult Initialize();

  std::vector<rhi::IRenderTarget*> Execute(const CFrameInput& input) const override;

private:

  TResult CreateRenderTarget(std::unique_ptr<rhi::IRenderTarget>& renderTarget);
  TResult CreateDepthBuffer();

  CBackend& m_backend;
  std::unique_ptr<rhi::IRenderTarget> m_pRenderTarget_Albedo;
  std::unique_ptr<rhi::IDepthBuffer> m_pDepthBuffer;
  std::vector<rhi::IRenderTarget*> m_renderTargets;
};
}
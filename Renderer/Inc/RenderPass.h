//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Backend/Inc/Instance.h>
#include "FrameInput.h"

namespace cge::render
{
//----------------------------------------------------
// IRenderPass
//----------------------------------------------------
class IRenderPass
{
public:

  virtual ~IRenderPass() = default;

  virtual void Execute(const CFrameInput& input) const = 0;
};

//----------------------------------------------------
// CGeometryPass
//----------------------------------------------------
class CGeometryPass final : public IRenderPass
{
public:

  CGeometryPass(rhi::IInstance& backend);

  void Execute(const CFrameInput& input) const override;

private:

  rhi::IInstance& m_backend;
};
}
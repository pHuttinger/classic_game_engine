//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "RenderPass.h"

namespace cge::render
{
class CGeometryPass final : public IRenderPass
{
public:

  CGeometryPass(CBackend& backend);

  TResult Initialize();

  void Execute(const CFrameInput& input) const override;

private:

  CBackend& m_backend;
};
}
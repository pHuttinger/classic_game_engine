//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Pipeline.h"
#include "DX11Instance.h"

namespace cge::rhi::dx11
{
class CPipeline : public IPipeline
{
public:

  CPipeline(IInstance& instance);

  void Clear() override;
  void Present() override;

private:

  CInstance& m_instance;
};
}
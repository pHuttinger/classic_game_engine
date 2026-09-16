//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "Renderer.h"

namespace cge::render
{
//----------------------------------------------------
// TShaderDataCreateInfo
//----------------------------------------------------
struct TShaderDataCreateInfo final
{
  size_t m_size = 0U;
};

//----------------------------------------------------
// CShaderData
//----------------------------------------------------
class CShaderData final
{
public:

  TResult Initialize(CRenderer& renderer, const TShaderDataCreateInfo& createInfo);

  void UpdateData(CRenderer& renderer, const TDataHandle& dataHandle);

private:

  std::unique_ptr<rhi::IBuffer> m_pBuffer;
};
}
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

  CShaderData(CRenderer& renderer);

  TResult Initialize(const TShaderDataCreateInfo& createInfo);

  void UpdateData(const TDataHandle& dataHandle);

private:

  CRenderer& m_renderer;

  std::unique_ptr<rhi::IBuffer> m_pBuffer;
};
}
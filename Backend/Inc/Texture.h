//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Common/Inc/Common.h>

namespace cge::rhi
{
//----------------------------------------------------
// TTextureCreateInfo
//----------------------------------------------------
struct TTextureCreateInfo final
{
  std::filesystem::path m_filename;
};

//----------------------------------------------------
// TTexture
//----------------------------------------------------
class ITexture
{
public:

  virtual ~ITexture() = default;

  virtual TResult Initialize(const TTextureCreateInfo& createInfo) = 0;
};
}
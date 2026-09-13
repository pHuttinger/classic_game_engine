//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common.h"

namespace cge::filesystem
{
//----------------------------------------------------
// TImageData
//----------------------------------------------------
struct TImageData final
{
  ~TImageData();

  unsigned char* m_data;
  int            m_width    = 0;
  int            m_height   = 0;
  int            m_channels = 0;
};

//----------------------------------------------------
// CImageLoader
//----------------------------------------------------
class CImageLoader final
{
public:

  TResult Load(const std::filesystem::path& filename, TImageData& imageData) const;
};
}
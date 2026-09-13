//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/FileSystem/ImageLoader.h""

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

namespace cge::filesystem
{
TImageData::~TImageData()
{
  if (m_data != nullptr)
  {
    stbi_image_free(m_data);
  }
}

TResult CImageLoader::Load(const std::filesystem::path& filename, TImageData& imageData) const
{
  imageData.m_data = stbi_load(
    filename.generic_string().c_str(),
    &imageData.m_width,
    &imageData.m_height,
    &imageData.m_channels,
    STBI_rgb_alpha
  );

  if (imageData.m_data == nullptr)
  {
    return TResult::Error("Failed to load Texture/Image from file");
  }

  return TResult::Okay();
}
}
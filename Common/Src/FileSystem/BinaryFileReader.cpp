//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/FileSystem/BinaryFileReader.h"
#include <fstream>

namespace cge::filesystem
{
TResult CBinaryFileReader::Read(const std::filesystem::path& filename, std::vector<char>& bytecode) const
{
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file)
    return TResult::Error("bin-file not found!");

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  bytecode.resize(size);
  if (!file.read(bytecode.data(), size))
    return TResult::Error("Failed to read bin-file!");

  return TResult::Okay();
}
}
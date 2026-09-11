//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "../Common.h"

namespace cge::filesystem
{
class CBinaryFileReader final
{
public:

  TResult Read(const std::filesystem::path& filename, std::vector<char>& bytecode) const;
};
}
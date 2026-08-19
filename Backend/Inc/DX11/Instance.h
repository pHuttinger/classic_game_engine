//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "../Instance.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace cge::rhi::dx11
{
class CInstance final : public IInstance
{
public:

  CInstance() = default;

private:


};
}
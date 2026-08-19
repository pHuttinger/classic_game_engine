//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Instance.h"
#include "../Inc/DX11/Instance.h"

namespace cge::rhi
{
//---------------------------------------------------
// CreateInstance - Helper - Function
//---------------------------------------------------
template <typename TInstance>
static TResult CreateInstance(std::unique_ptr<IInstance>& pInstanceInterface)
{
  auto pInstance = std::make_unique<TInstance>();
  pInstanceInterface = std::move(pInstance);
  return TResult::Okay();
}

//---------------------------------------------------
// CreateInstance - Function
//---------------------------------------------------
TResult CreateInstance(const EBackend backend,
                       std::unique_ptr<IInstance>& pInstance)
{
  switch (backend)
  {
    case EBackend::DX11  : return CreateInstance<dx11::CInstance>(pInstance);
    case EBackend::OpenGL: return TResult::Error("OpenGL is not implemented yet!");
  }

  return TResult::Error("invalid 'lpe::rhi::EBackend'!");
}
}
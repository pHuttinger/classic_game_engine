//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/DX11/DX11Instance.h"

namespace cge::rhi
{
//---------------------------------------------------
// CreateInstance - Helper - Function
//---------------------------------------------------
template <typename TInstance>
static TResult TCreateInstance(const TCreateInfo& createInfo, std::unique_ptr<IInstance>& pInstanceInterface)
{
  auto pInstance = std::make_unique<TInstance>();
  TInstance* pInstanceRaw = pInstance.get();
  pInstanceInterface = std::move(pInstance);
  return pInstanceRaw->Create(createInfo);
}

//---------------------------------------------------
// CreateInstance - Function
//---------------------------------------------------
TResult CreateInstance(const TCreateInfo& createInfo, std::unique_ptr<IInstance>& pInstance)
{
  switch (createInfo.m_backend)
  {
    case EBackend::DX11  : return TCreateInstance<dx11::CInstance>(createInfo, pInstance);
    case EBackend::OpenGL: return TResult::Error("OpenGL is not implemented yet!");
  }

  return TResult::Error("invalid 'lpe::rhi::EBackend'!");
}
}
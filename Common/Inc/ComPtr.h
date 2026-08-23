//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

namespace cge
{
template <typename T>
class CComPtr final
{
public:

  T*& Get()
  {
    return m_pPtr;
  }

  ~CComPtr()
  {
    if (m_pPtr != nullptr)
    {
      m_pPtr->Release();
    }
  }

private:

  T* m_pPtr = nullptr;
};
}
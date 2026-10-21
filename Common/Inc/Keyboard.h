//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <array>

namespace cge
{
constexpr uint32_t CGE_KEY_COUNT = 256U;

class CKeyboard
{
friend class CInstance;
friend class CWindow;

public:

  CKeyboard() = delete;

  static bool IsKeyDown(uint32_t key);
  static bool IsKeyPressed(uint32_t key);
  static bool IsKeyReleased(uint32_t key);

  static void EndFrame();

private:

  static void OnKeyDown(uint32_t key);
  static void OnKeyUp(uint32_t key);

  static inline std::array<bool, CGE_KEY_COUNT> m_currentState;
  static inline std::array<bool, CGE_KEY_COUNT> m_previousState;
};
}

//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/Keyboard.h"

namespace cge
{
//static
void CKeyboard::OnKeyDown(uint32_t key)
{
  if (key < CGE_KEY_COUNT)
  {
    m_currentState[key] = true;
  }
}

//static
void CKeyboard::OnKeyUp(uint32_t key)
{
  if (key < CGE_KEY_COUNT)
  {
    m_currentState[key] = false;
  }
}

//static
bool CKeyboard::IsKeyDown(uint32_t key)
{
  return key < CGE_KEY_COUNT && m_currentState[key];
}

//static
bool CKeyboard::IsKeyPressed(uint32_t key)
{
  return key < CGE_KEY_COUNT && m_currentState[key] && !m_previousState[key];
}

//static
bool CKeyboard::IsKeyReleased(uint32_t key)
{
  return key < CGE_KEY_COUNT && !m_currentState[key] && m_previousState[key];
}

//static
void CKeyboard::EndFrame()
{
  m_previousState = m_currentState;
}
}

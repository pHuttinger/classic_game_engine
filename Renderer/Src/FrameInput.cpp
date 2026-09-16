//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../Inc/FrameInput.h"

constexpr glm::vec4 DEFAULT_CLEAR_COLOR = glm::vec4(0.1f, 0.3f, 0.5f, 1.0f);

namespace cge::render
{
CFrameInput::CFrameInput()
{
  Reset();
}

void CFrameInput::Reset()
{
  m_clearColor = DEFAULT_CLEAR_COLOR;
  m_pMeshes.clear();
}
}
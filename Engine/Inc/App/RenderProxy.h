////////////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include <Renderer/Inc/Renderer.h>

namespace cge
{
class CRenderProxy final
{
public:

  CRenderProxy();

  TResult Initialize(const rhi::TCreateInfo& createInfo);

  void Open();
  void Present();
  //void SetViewInfo(const rendering::TRenderFrameViewInfo& viewInfo);
  //void FrameAddStaticMesh(rendering::CStaticMesh* pStaticMesh);

  //glm::vec2 GetViewportSize() const { return m_renderer.GetViewportSize(); }
  //const rendering::CStaticMeshFactory& GetStaticMeshFactory() const { return m_staticMeshFactory; }

private:

  render::CRenderer m_renderer;
  //rendering::CStaticMeshFactory m_staticMeshFactory;
  //lpe::rendering::CRenderFrameInput m_renderFrameInput;
};
}
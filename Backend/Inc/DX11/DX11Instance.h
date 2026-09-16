//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#pragma once

#include "DX11.h"
#include "../Instance.h"

namespace cge::rhi::dx11
{
class CInstance final : public IInstance
{
public:

  CInstance() = default;
  ~CInstance();

  TResult Create(const TCreateInfo& createInfo);

  std::unique_ptr<IPipeline> CreatePipeline() override;

  TResult CreateSurface(const TSurfaceCreateInfo& createInfo, std::unique_ptr<ISurface>& pSurface) override;
  TResult CreateRenderTarget(const TRenderTargetCreateInfo& createInfo, std::unique_ptr<IRenderTarget>& pRenderTarget) override;
  TResult CreateDepthBuffer(const TDepthBufferCreateInfo& createInfo, std::unique_ptr<IDepthBuffer>& pDepthBuffer) override;
  TResult CreatePixelShader(const TPixelShaderCreateInfo& createInfo, std::unique_ptr<IPixelShader>& pPixelShader) override;
  TResult CreateVertexShader(const TVertexShaderCreateInfo& createInfo, std::unique_ptr<IVertexShader>& pVertexShader) override;
  TResult CreateSampler(std::unique_ptr<ISampler>& pSampler) override;
  TResult CreateBuffer(const TBufferCreateInfo& createInfo, std::unique_ptr<IBuffer>& pBuffer)override;
  TResult CreateVertexDescriptor(const TVertexDescriptorCreateInfo& createInfo, std::unique_ptr<IVertexDescriptor>& pVertexDescriptor) override;
  TResult CreateTexture(const TTextureCreateInfo& createInfo, std::unique_ptr<ITexture>& pTexture) override;

  std::string GetShaderFilename(const std::string& shaderName) override;

  ID3D11Device* GetDevice() { return m_pDevice.Get(); }
  ID3D11DeviceContext* GetDeviceContext() { return m_pDeviceContext.Get(); }
  IDXGISwapChain* GetSwapChain() { return m_pSwapChain.Get(); }

private:

  TResult CreateDeviceAndSwapchain(const TCreateInfo& createInfo);

  CComPtr<ID3D11Device>        m_pDevice;
  CComPtr<ID3D11DeviceContext> m_pDeviceContext;
  CComPtr<IDXGISwapChain>      m_pSwapChain;
};
}
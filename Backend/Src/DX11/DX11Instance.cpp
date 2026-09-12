/////////////////////////////////////////////////////
// Copyright (C) BifrostDev 2026 - LPE game engine //
/////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Instance.h"
#include "../../Inc/DX11/DX11Pipeline.h"
#include "../../Inc/DX11/DX11Surface.h"
#include "../../Inc/DX11/DX11RenderTarget.h"
#include "../../Inc/DX11/DX11DepthBuffer.h"
#include "../../Inc/DX11/DX11PixelShader.h"
#include "../../Inc/DX11/DX11VertexShader.h"
#include "../../Inc/DX11/DX11Sampler.h"
#include "../../Inc/DX11/DX11Buffer.h"
#include "../../Inc/DX11/DX11VertexDescriptor.h"

namespace cge::rhi::dx11
{
CInstance::~CInstance()
{
  m_pSwapChain.Get()->SetFullscreenState(false, nullptr);
}

TResult CInstance::Create(const TCreateInfo& createInfo)
{
  DXGI_MODE_DESC bufferDesc{};
  bufferDesc.Width                   = createInfo.m_width;
  bufferDesc.Height                  = createInfo.m_height;
  bufferDesc.RefreshRate.Denominator = 1;
  bufferDesc.RefreshRate.Numerator   = 60;
  bufferDesc.Format                  = CGE_DEFAULT_DXGI_FORMAT;
  bufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  bufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;

  DXGI_SWAP_CHAIN_DESC swapChainDesc{};
  swapChainDesc.BufferDesc         = bufferDesc;
  swapChainDesc.SampleDesc.Count   = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  swapChainDesc.BufferUsage        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.BufferCount        = 1;
  swapChainDesc.OutputWindow       = createInfo.m_hwnd;
  swapChainDesc.Windowed           = !createInfo.m_fullscreen;
  swapChainDesc.SwapEffect         = DXGI_SWAP_EFFECT_DISCARD;

  HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
                                             D3D_DRIVER_TYPE_HARDWARE,
                                             nullptr,
                                             0,
                                             nullptr,
                                             0,
                                             D3D11_SDK_VERSION,
                                             &swapChainDesc,
                                             &m_pSwapChain.Get(),
                                             &m_pDevice.Get(),
                                             nullptr,
                                             &m_pDeviceContext.Get());

  CGE_HRESULT_CHECK(hr, "can't create device and swapchain");

  return TResult::Okay();
}

std::unique_ptr<IPipeline> CInstance::CreatePipeline()
{
  return std::make_unique<CPipeline>(*this);
}

TResult CInstance::CreateSurface(const TSurfaceCreateInfo& createInfo, std::unique_ptr<ISurface>& pSurface)
{
  pSurface = std::make_unique<CSurface>(*this);
  return pSurface->Initialize(createInfo);
}

TResult CInstance::CreateRenderTarget(const TRenderTargetCreateInfo& createInfo, std::unique_ptr<IRenderTarget>& pRenderTarget)
{
  pRenderTarget = std::make_unique<CRenderTarget>(*this);
  return pRenderTarget->Initialize(createInfo);
}

TResult CInstance::CreateDepthBuffer(const TDepthBufferCreateInfo& createInfo, std::unique_ptr<IDepthBuffer>& pDepthBuffer)
{
  pDepthBuffer = std::make_unique<CDepthBuffer>(*this);
  return pDepthBuffer->Initialize(createInfo);
}

TResult CInstance::CreatePixelShader(const TPixelShaderCreateInfo& createInfo, std::unique_ptr<IPixelShader>& pPixelShader)
{
  pPixelShader = std::make_unique<CPixelShader>(*this);
  return pPixelShader->Initialize(createInfo);
}

TResult CInstance::CreateVertexShader(const TVertexShaderCreateInfo& createInfo, std::unique_ptr<IVertexShader>& pVertexShader)
{
  pVertexShader = std::make_unique<CVertexShader>(*this);
  return pVertexShader->Initialize(createInfo);
}

TResult CInstance::CreateSampler(std::unique_ptr<ISampler>& pSampler)
{
  pSampler = std::make_unique<CSampler>(*this);
  return pSampler->Initialize();
}

TResult CInstance::CreateBuffer(const TBufferCreateInfo& createInfo, std::unique_ptr<IBuffer>& pBuffer)
{
  pBuffer = std::make_unique<CBuffer>(*this);
  return pBuffer->Initialize(createInfo);
}

TResult CInstance::CreateVertexDescriptor(const TVertexDescriptorCreateInfo& createInfo, std::unique_ptr<IVertexDescriptor>& pVertexDescriptor)
{
  pVertexDescriptor = std::make_unique<CVertexDescriptor>(*this);
  return pVertexDescriptor->Initialize(createInfo);
}

std::string CInstance::GetShaderFilename(const std::string& shaderName)
{
  return "./" + shaderName + ".cso";
}
}
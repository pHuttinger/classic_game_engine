//////////////////////////////////////////////////////
// Copyright (C) P.Huttinger 2026 - CGE game engine //
//////////////////////////////////////////////////////

#include "../../Inc/DX11/DX11Texture.h"
//TODO switch to binary input!
#include <Common/Inc/FileSystem/ImageLoader.h>

namespace cge::rhi::dx11
{
CTexture::CTexture(IInstance& instance)
  : m_instance(static_cast<CInstance&>(instance))
{
}

TResult CTexture::Initialize(const TTextureCreateInfo& createInfo)
{
  filesystem::CImageLoader imageLoader;
  filesystem::TImageData imageData;
  CGE_TRY(imageLoader.Load(createInfo.m_filename, imageData));

  D3D11_TEXTURE2D_DESC desc{};
  desc.Width            = imageData.m_width;
  desc.Height           = imageData.m_height;
  desc.MipLevels        = 0;
  desc.ArraySize        = 1;
  desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.SampleDesc.Count = 1;
  desc.Usage            = D3D11_USAGE_DEFAULT;
  desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
  desc.MiscFlags        = D3D11_RESOURCE_MISC_GENERATE_MIPS;

  const uint32_t memPitch = imageData.m_width * 4U;

  D3D11_SUBRESOURCE_DATA initData{};
  initData.pSysMem     = imageData.m_data;
  initData.SysMemPitch = memPitch;

  ID3D11Texture2D* texture = nullptr;
  HRESULT hr = m_instance.GetDevice()->CreateTexture2D(&desc, nullptr, &texture);
  CGE_HRESULT_CHECK(hr, "Failed to create Texture2D");

  m_instance.GetDeviceContext()->UpdateSubresource(
    texture,
    0U,
    nullptr,
    imageData.m_data,
    memPitch,
    0U
  );

  hr = m_instance.GetDevice()->CreateShaderResourceView(texture, nullptr, &m_pShaderResourceView.Get());
  CGE_HRESULT_CHECK(hr, "Failed to create ShaderResouceView");

  texture->Release();

  m_instance.GetDeviceContext()->GenerateMips(m_pShaderResourceView.Get());

  return TResult::Okay();
}
}

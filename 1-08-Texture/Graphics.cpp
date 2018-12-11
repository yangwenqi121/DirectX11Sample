﻿#include <vector>
#include "Window.hpp"
#include "Graphics.hpp"

Microsoft::WRL::ComPtr<ID3D11Device> Graphics::device;
Microsoft::WRL::ComPtr<ID3D11DeviceContext> Graphics::context;
Microsoft::WRL::ComPtr<IDXGISwapChain> Graphics::swapChain;
Microsoft::WRL::ComPtr<IWICImagingFactory> Graphics::imageFactory;

void Graphics::Initialize()
{
    std::vector<D3D_DRIVER_TYPE> driverTypes
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
        D3D_DRIVER_TYPE_SOFTWARE,
    };

    std::vector<D3D_FEATURE_LEVEL> featureLevels
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferDesc.Width = Window::GetSize().x;
    swapChainDesc.BufferDesc.Height = Window::GetSize().y;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = Window::GetHandle();
    swapChainDesc.Windowed = true;

    for (size_t i = 0; i < driverTypes.size(); i++)
    {
        HRESULT r = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[i], nullptr, 0, featureLevels.data(), (UINT)featureLevels.size(), D3D11_SDK_VERSION, &swapChainDesc, swapChain.GetAddressOf(), device.GetAddressOf(), nullptr, context.GetAddressOf());

        if (SUCCEEDED(r))
            break;
    }

    D3D11_VIEWPORT viewport = {};
    viewport.Width = (float)Window::GetSize().x;
    viewport.Height = (float)Window::GetSize().y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    context->RSSetViewports(1, &viewport);

    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(imageFactory.GetAddressOf()));
}

ID3D11Device& Graphics::GetDevice()
{
    return *device.Get();
}

ID3D11DeviceContext& Graphics::GetContext()
{
    return *context.Get();
}

IDXGISwapChain& Graphics::GetSwapChain()
{
    return *swapChain.Get();
}

IWICImagingFactory& Graphics::GetImageFactory()
{
    return *imageFactory.Get();
}

void Graphics::Update()
{
    swapChain->Present(1, 0);
}
﻿#include "Window.hpp"
#include "Graphics.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

void Initialize()
{
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Window::Initialize();
    Graphics::Initialize();
}

bool Refresh()
{
    Graphics::Update();
    return Window::Update();
}

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    Initialize();

    auto camera = std::make_unique<Camera>();
    auto mesh = Mesh::CreateTriangle();

    while (Refresh())
    {
        camera->Start();
        mesh->Draw();
        camera->Stop();
    }

    return 0;
}
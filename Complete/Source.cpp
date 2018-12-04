﻿// Source.cpp
#include "Window.hpp"
#include "Graphics.hpp"

#include "CBuffer.hpp"
#include "Texture.hpp"
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

    Camera camera;
    camera.position = DirectX::XMFLOAT3(0.0f, 2.0f, -2.0f);
    camera.rotation = DirectX::XMFLOAT3(45.0f, 0.0f, 0.0f);

    std::unique_ptr<Texture> texture = Texture::CreateFromFile(L"Texture.jpg");

    Mesh mesh;
    mesh.texture = *texture;
    mesh.CreateCube(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));

    float angle = 0.0f;

    while (Refresh())
    {
        camera.Start();
        
        angle += 1.0f;

        mesh.rotation.y = angle;
        mesh.Draw();

        camera.Stop();
    }

    return 0;
}

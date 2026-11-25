#include "ui/LoadingLogoScenes.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/TextureManagerF198.hpp"
#include "graphics/SpriteQuad.hpp"
#include "graphics/SpriteTransform.hpp"
#include <windows.h>

void LoadingScene::Render()
{
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quad;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        {
            RECT rectangle;
            SetRect(&rectangle, 0, 0, 640, 480);
            reinterpret_cast<SpriteTransform*>(&quad)->BuildQuadFromRect(&rectangle);
            texture->DrawQuad(0, quad, &rectangle, 0xffffffff);
        }
        Graphics::EndFrame();
    }
}

void LogoScene::Render()
{
    if (Graphics::BeginFrame()) {
        SpriteQuad40CA80 quad;
        texture->SetDepthMode(0);
        texture->SetBlendMode(0);
        {
            RECT rectangle;
            SetRect(&rectangle, 0, 0, 640, 480);
            reinterpret_cast<SpriteTransform*>(&quad)->BuildQuadFromRect(&rectangle);
            texture->DrawQuad(0, quad, &rectangle, 0xffffffff);
        }
        Graphics::EndFrame();
    }
}

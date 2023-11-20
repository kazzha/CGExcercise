#include "BitmapExample.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

HRESULT BitmapExample::CreateDeviceResources()
{
    D2DFramework::CreateDeviceResources();

    HRESULT hr = mspRenderTarget->CreateBitmap(
        D2D1::SizeU(BITMAP_WIDTH, BITMAP_HEIGHT),
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
        mspFrameBuffer.ReleaseAndGetAddressOf()
    ); // 만약 만들어져있으면 해제하고 다시 포인터를 가져오다..
    ThrowIfFailed(hr);

    return S_OK;
}

HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
	D2DFramework::Initialize(hInstance, title, w, h);

    mspBackBuffer = std::make_unique<UINT8[]>(BITMAP_WIDTH * BITMAP_HEIGHT * BITMAP_BYTECOUNT);

   
    return S_OK;
}

void BitmapExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    ClearBuffer(D2D1::ColorF(D2D1::ColorF::PapayaWhip));
    //DrawRectangle(0, 0, 100, 100, D2D1::ColorF::Red);
    //DrawRectangle(50, 50, 100, 100, D2D1::ColorF(D2D1::ColorF::Gray, 0.7f));
    //DrawCircle(100, 100, 100, D2D1::ColorF::Red);
    DrawLine(0, 0, 100, 100, D2D1::ColorF::Red);
    PresentBuffer();
    mspRenderTarget->DrawBitmap(mspFrameBuffer.Get());

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void BitmapExample::DrawPixel(int x, int y, D2D1::ColorF color)
{
    int pitch = BITMAP_WIDTH * BITMAP_BYTECOUNT;
    int i = y * pitch + x * BITMAP_BYTECOUNT;

    float inverse = 1.0f - color.a;

    mspBackBuffer[i] = static_cast<UINT8>(mspBackBuffer[i]* inverse + static_cast<UINT8>(color.r * 255 * color.a));
    mspBackBuffer[i+1] = static_cast<UINT8>(mspBackBuffer[i+1] * inverse + static_cast<UINT8>(color.g * 255 * color.a));
    mspBackBuffer[i+2] = static_cast<UINT8>(mspBackBuffer[i+2] * inverse + static_cast<UINT8>(color.b * 255 * color.a));
    mspBackBuffer[i+3] = static_cast<UINT8> (mspBackBuffer[i+3] * inverse + static_cast<UINT8>(color.a * 255 * color.a));
}

void BitmapExample::DrawRectangle(int left, int top, int w, int h, D2D1::ColorF color)
{
    for (int x = 0; x < w; ++x)
    {
        for (int y = 0; y < h; ++y)
        {
            DrawPixel(left+x, top+y, color);
        }
    }
}

void BitmapExample::DrawCircle(int x, int y, int r, D2D1::ColorF color)
{
    double degree{}, radian{};
    for (int i = 0; i < 360; i++)
    {
        radian = degree * M_PI / 180;
        DrawPixel(x + cos(radian) * r, y + sin(radian) * r, color);
        degree++;
    }
}

void BitmapExample::DrawLine(int x1, int y1, int x2, int y2, D2D1::ColorF color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int maxY = max(y1, y2);
    int minY = min(y1, y2);

    if (dx == 0)
    {
        if (dy > 0)
        {
            for (int i = y1; i != y2; i++)
            {
                DrawPixel(x1, i, color);
            }
        }
        else if (dy < 0)
        {
            for (int i = y1; i != y2; i--)
            {
                DrawPixel(x1, i, color);
            }
        }
    }
    else if (dy == 0)
    {
        if (dx > 0)
        {
            for (int i = x1; i != x2; i++)
            {
                DrawPixel(i, y1, color);
            }
        }
        else if (dx < 0)
        {
            for (int i = x1; i != x2; i--)
            {
                DrawPixel(i, y1, color);
            }
        }
    }

    else
    {
        float m = static_cast<float>(dy) / dx;
        float y{};
        if (m > 0)
        {
            if (dx < 0)
            {
                for (int i = x1; i != x2; i--)
                {
                    y = m * (i - x1) + (float)y1;
                    DrawPixel(i, y, color);
                }
            }
            else if (dx > 0)
            {
                for (int i = x1; i != x2; i++)
                {
                    y = m * (i - x1) + (float)y1;
                    DrawPixel(i, y, color);
                }
            }
        }
        else if (m < 0)
        {
            if (dx < 0)
            {
                for (int i = x1; i != x2; i--)
                {
                    y = m * (i - x1) + (float)y1;
                    DrawPixel(i, y, color);
                }
            }
            else if (dx > 0)
            {
                for (int i = x1; i != x2; i++)
                {
                    y = m * (i - x1) + (float)y1;
                    DrawPixel(i, y, color);
                }
            }
        }
    }

    }
   
   



void BitmapExample::ClearBuffer(D2D1::ColorF color)
{
    UINT8* p = &mspBackBuffer[0];
    for (int i = 0; i < BITMAP_WIDTH * BITMAP_HEIGHT; i++)
    {
        *p++ = static_cast<UINT8>(color.r * 255);
        *p++ = static_cast<UINT8>(color.g * 255);
        *p++ = static_cast<UINT8>(color.b * 255);
        *p++ = static_cast<UINT8>(color.a * 255);
    } // *p일 때의 값을 넣고(4개 값) ++로 순회
}

void BitmapExample::PresentBuffer()
{
    mspFrameBuffer->CopyFromMemory(nullptr, &mspBackBuffer[0], BITMAP_WIDTH * BITMAP_BYTECOUNT);
}

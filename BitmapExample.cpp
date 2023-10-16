#include "BitmapExample.h"

HRESULT BitmapExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
	D2DFramework::Initialize(hInstance, title, w, h);

	// 우리가 할 일 - 백버퍼 채우고, 프론트 버퍼 준비
}

void BitmapExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    // 그리기

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

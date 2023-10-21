#pragma once
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
const int BITMAP_BYTECOUNT = 4;

class BitmapExample : public D2DFramework
{
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBuffer;
	std::unique_ptr<UINT8[]> mspBackBuffer; // back를 frame으로 복사하면 화면에 나타남

	// UINT array[1024 * 768 * 4]; -> 정적할당은 stack이라는 작은 공간에 올라가기 때문에
	// 데이터를 다룰 때는 거의 쓸 수 없음.

protected:
	virtual HRESULT CreateDeviceResources() override;

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"BitmapExample",
		UINT w = BITMAP_WIDTH, UINT h = BITMAP_HEIGHT) override;
	virtual void Render() override;

	void DrawPixel(int x, int y, D2D1::ColorF color);
	void DrawRectangle(int left, int top, int w, int h, D2D1::ColorF color);
	void DrawCircle(int x, int y, int r, D2D1::ColorF color);
	void DrawLine(int x, int y, int x2, int y2, D2D1::ColorF color);
	void ClearBuffer(D2D1::ColorF color);

	void PresentBuffer();

};


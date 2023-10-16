#pragma once
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
const int BITMAP_BYTECOUBT = 4;

class BitmapExample : public D2DFramework
{
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspFrameBuffer;
	std::unique_ptr<UINT8[]> mspBackBuffer; // back를 frame으로 복사하면 화면에 나타남

public:
	virtual HRESULT Initialize(HINSTANCE hInstance, LPCWSTR title = L"BitmapExample",
		UINT w = BITMAP_WIDTH, UINT h = BITMAP_HEIGHT) override;
	virtual void Render() override;

};


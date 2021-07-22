#pragma once
#include <windows.h>
#include <WindowsX.h>
#include <math.h>

class BaseObject
{
protected:
	int posX;
	int posY;
	int formX;
	int formY;
	HBITMAP hBitmap, hbmMask;
	HINSTANCE hInst;
	HDC hdcMem;
	HGDIOBJ oldBitmap;
	BITMAP bitmap;
public:

	BaseObject();
	~BaseObject();

	int GetPosX();
	int GetPosY();
	void SetPosX(int a_posX);
	void SetPosY(int a_posY);
	void IncresePosX(int a);
	void IncresePosY(int a);
	virtual void Draw(HWND hwnd, HDC hdc);
	HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);


	static int mapSlider;
	static int clousDrifting;
};


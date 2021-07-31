#pragma once
#include "BaseObject.h"
#include "Map.h"

#define MENU_HEIGHT 536
#define MENU_WIDTH 1000
#define SELECTION_HEIGHT 81
#define SELECTION_WIDTH 352



class Menu : public BaseObject
{
private:
	HBITMAP hBitmap_Menu;
public:

	Menu()
	{
		posX = 55;
		posY = 45;
		formX = 0;
		hBitmap_Menu = (HBITMAP)LoadImage(hInst, L"Menu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
		hBitmap = (HBITMAP)LoadImage(hInst, L"Selection.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hbmMask = CreateBitmapMask(hBitmap, RGB(255, 255, 255));
	}

	~Menu()
	{

	}

	void ChangeSelection()
	{
		if (posY == 155)
		{
			posY = 45;
		}
		else
			posY = 155;
	}


	void Draw(HWND hwnd, HDC hdc, HDC hdcMem) override
	{
		//hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap_Menu);
		GetObject(hBitmap_Menu, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			0,
			0,
			MENU_WIDTH,
			MENU_HEIGHT,
			hdcMem,
			0,
			0,
			SRCCOPY
		);
		//------
		//Select
		oldBitmap = SelectObject(hdcMem, hbmMask);
		GetObject(hbmMask, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX,
			posY,
			SELECTION_WIDTH,
			SELECTION_HEIGHT,
			hdcMem,
			SELECTION_WIDTH * formX,
			0,
			SRCAND
		);
		oldBitmap = SelectObject(hdcMem, hBitmap);
		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt
		(
			hdc,
			posX,
			posY,
			SELECTION_WIDTH,
			SELECTION_HEIGHT,
			hdcMem,
			SELECTION_WIDTH * formX,
			0,
			SRCPAINT
		);
		if (formX >= 3)
		{
			formX = 0;
		}
		else
			formX++;
		//SelectObject(hdcMem, oldBitmap);
		//DeleteDC(hdcMem);
	}

	bool CheckExit()
	{
		if (posY == 155)
			return true;
		return false;
	}

};
#pragma once
#include "framework.h"

class VectorDraw
{
private:
	char dataFromClipboard[1024];
public:
	long GetFromClipboard(HWND hWnd, long maxsize);
};
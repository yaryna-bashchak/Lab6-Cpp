#include "vector_draw.h"

long VectorDraw::GetFromClipboard(HWND hWnd, long maxsize)
{
	HGLOBAL hglb;
	LPTSTR lptstr;
	long size, res = 0;

	if (!IsClipboardFormatAvailable(CF_TEXT)) return 0;
	
	if (!OpenClipboard(hWnd)) return 0;
	hglb = GetClipboardData(CF_TEXT);

	if (hglb != NULL)
	{
		lptstr = (LPTSTR)GlobalLock(hglb);
		if (lptstr != NULL)
		{
			size = strlen((char*)lptstr);
			if (size > maxsize)
			{
				lptstr[maxsize] = 0;
				size = strlen((char*)lptstr);
			}
			strcpy_s(dataFromClipboard, (char*)lptstr);
			res = size;
			GlobalUnlock(hglb);
		}
	}
	CloseClipboard();
	return res;
}

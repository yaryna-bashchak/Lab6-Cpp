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

void VectorDraw::ParseClipboard()
{
    myVector.clear();

    if (dataFromClipboard)
    {
        string data = string(dataFromClipboard);
        size_t pos1 = 0;
        string sep1 = "\n";

        while ((pos1 = data.find(sep1)) != string::npos)
        {
            string line = data.substr(0, pos1);
            data.erase(0, pos1 + sep1.length());

            if (line != "")
            {
                double value;
                size_t pos2 = 0;
                string sep2 = "\t";

                pos2 = line.find(sep2);
                value = stod(line.substr(pos2 + sep2.length(), line.length()));
                myVector.push_back(value);
            }
        }
    }
}

void VectorDraw::OnPaint(HDC hdc)
{
	DrawAxis(hdc);
	DrawVector(hdc);
}

void VectorDraw::DrawAxis(HDC hdc)
{
	SelectObject(hdc, hPen);

	MoveToEx(hdc, x1 - dArrow, y1 + dArrow, NULL);
	LineTo(hdc, x1, y1);
	LineTo(hdc, x1 + dArrow, y1 + dArrow);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x2, y2);

	MoveToEx(hdc, x2 - dArrow, y2 - dArrow, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x2 - dArrow, y2 + dArrow);
}

void VectorDraw::DrawVector(HDC hdc)
{

}

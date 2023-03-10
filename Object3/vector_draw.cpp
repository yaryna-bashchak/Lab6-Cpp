#include "vector_draw.h"

void VectorDraw::GetFromClipboard(HWND hWnd, long maxsize)
{
	HGLOBAL hglb;
	LPTSTR lptstr;
	long size, res = 0;

	if (IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(hWnd))
	{ 
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
	
		ParseClipboard();
		InvalidateRect(hWnd, NULL, TRUE);
	}
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
	DrawNumbers(hdc);
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

void VectorDraw::DrawNumbers(HDC hdc)
{
	dx = (x2 - x1 - 50) / myVector.size();

	max = max_element(myVector.begin(), myVector.end());
	min = min_element(myVector.begin(), myVector.end());

	dy = (y2 - y1 - 50) / (*max - *min + 1);

	for (size_t i = 0; i < myVector.size(); i++)
	{
		int xCoord = x1 + dx * (i + 1);
		MoveToEx(hdc, xCoord, y2 - 5, NULL);
		LineTo(hdc, xCoord, y2 + 5);
		TextOut(hdc, xCoord - 5, y2 + 15, to_wstring(i + 1).c_str(), wcslen(to_wstring(i + 1).c_str()));
	}

	for (size_t i = 0; i < *max - *min + 1; i++)
	{
		int yCoord = y2 - dy * (i + 1);
		MoveToEx(hdc, x1 - 5, yCoord, NULL);
		LineTo(hdc, x1 + 5, yCoord);

		WCHAR y[32];
		swprintf_s(y, 32, L"%0.f", *min + i);
		TextOut(hdc, x1 - 40, yCoord - 8, wstring(y).c_str(), wcslen(wstring(y).c_str()));
	}
}

void VectorDraw::DrawVector(HDC hdc)
{
	if (myVector[0])
	{
		MoveToEx(hdc, x1 + dx, y2 - dy * (myVector[0] - *min + 1), NULL);
		LineTo(hdc, x1 + dx, y2 - dy * (myVector[0] - *min + 1));
	}

	for (size_t i = 1; i < myVector.size(); i++)
	{
		LineTo(hdc, x1 + dx * (i + 1), y2 - dy * (myVector[i] - *min + 1));
	}
}

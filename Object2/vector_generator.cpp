#include "vector_generator.h"
#include <cstdlib>
#include <codecvt>

void VectorGenerator::OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    COPYDATASTRUCT* cds;

    cds = (COPYDATASTRUCT*)lParam;
    int* p = (int*)cds->lpData;
    n = p[0];
    min = p[1];
    max = p[2];

    Generate();
	InvalidateRect(hWnd, NULL, TRUE);
	//ShowVector(hWnd);
}

void VectorGenerator::Generate()
{
    double num;
    myVector.clear();

    for (size_t i = 0; i < n; i++)
    {
        num = min + rand() % (max - min + 1);
        myVector.push_back(num);
    }
}

void VectorGenerator::ShowVector(HWND hWnd, HDC hdc)
{
	/*using convert_type = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;*/

	int left = 60;
	int top = 15;
	int dH = 50;
	int dV = 20;

	//PAINTSTRUCT ps;
	//HDC hdc = BeginPaint(hWnd, &ps);

	/*string sElem;
	wstring wsElem;
	double elem;*/
	TextOut(hdc, left, top, L"x", 1);
	TextOut(hdc, left + dH, top, L"y", 1);
	top += dV;
	
	for (int i = 0; i < myVector.size(); i++)
	{
		WCHAR wx[64];
		WCHAR wy[64];
		swprintf_s(wx, 64, L"%d", i + 1);
		swprintf_s(wy, 64, L"%0.f", myVector[i]);

		wstring first = wstring(wx);
		wstring second = wstring(wy);
		TextOut(hdc, left, top, first.c_str(), wcslen(first.c_str()));
		TextOut(hdc, left + dH, top, second.c_str(), wcslen(second.c_str()));

		top += dV;
	}
	//InvalidateRect(hWnd, NULL, TRUE);
	/*int x = 20, y = 25;

	for (int i = 0; i < nPoint; i++)
	{

		stringstream ss1, ss2;
		elem = pointsArray[i][0];
		ss1 << elem;
		ss1 >> sElem;
		wsElem = converter.from_bytes(sElem);
		TextOut(hdc, x, y, (LPCWSTR)wsElem.c_str(), (int)wcslen((LPCWSTR)wsElem.c_str()));

		x += 50;

		elem = pointsArray[i][1];
		ss2 << elem;
		ss2 >> sElem;
		wsElem = converter.from_bytes(sElem);
		TextOut(hdc, x, y, (LPCWSTR)wsElem.c_str(), (int)wcslen((LPCWSTR)wsElem.c_str()));
		x = 20;
		y += 20;
	}*/

	/*TextOut(hdc, 150, 100, text, wcslen(text));*/
	//EndPaint(hWnd, &ps);
}

/*
std::string PointsDisplay::GetArrayStr(int** arraySource, int num)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;

	std::string result;
	std::ostringstream stream;
	int elementx, elementy;

	for (int i = 0; i < num; i++)
	{
		elementx = arraySource[i][0];
		elementy = arraySource[i][1];
		stream << elementx << '\t' << elementy;
		stream << '\n';
	}
	result = stream.str();

	return result;
}

int PointsDisplay::PutTextToClipboard(HWND hWnd, const char* src)
{
	HGLOBAL hglbCopy;
	BYTE* pTmp;
	long len;

	if (src == NULL) return 0;
	if (src[0] == 0) return 0;

	len = (long)strlen(src);
	hglbCopy = GlobalAlloc(GHND, len + 1);

	if (hglbCopy == NULL) return 0;

	pTmp = (BYTE*)GlobalLock(hglbCopy);
	memcpy(pTmp, src, len + 1);
	GlobalUnlock(hglbCopy);

	if (!OpenClipboard(hWnd))
	{
		GlobalFree(hglbCopy);
		return 0;
	}

	EmptyClipboard();
	SetClipboardData(CF_TEXT, hglbCopy);
	CloseClipboard();

	return 1;
}*/
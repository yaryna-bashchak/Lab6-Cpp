#include "framework.h"
#include "vector_params.h"
#include "resource1.h"

static INT_PTR CALLBACK VectorParams(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

int OpenDialog(HWND hWnd, HINSTANCE hInst)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, VectorParams);
}
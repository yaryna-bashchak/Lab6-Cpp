#include "framework.h"
#include "vector_params.h"
#include "resource1.h"

int n, min, max;
BOOL pn, pmin, pmax;
HWND hWndObject2, hWndObject3;

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
            n = GetDlgItemInt(hDlg, IDC_EDIT_N, &pn, FALSE);
            min = GetDlgItemInt(hDlg, IDC_EDIT_MIN, &pmin, FALSE);
            max = GetDlgItemInt(hDlg, IDC_EDIT_MAX, &pmax, FALSE);
            
            if (pn == 0 || pmin == 0 || pmax == 0)
            {
                MessageBox(hDlg, L"Ви ввели текст, який не може бути інтерпретоване як число, або залишили рядок пустим.", L"Упс, помилка", MB_OK);
                break;
            }

            if (n <= 0 || min <= 0 || max <= 0 || max <= min)
            {
                MessageBox(hDlg, L"Не всі введені вами числа є коректними.\n\nВимоги: жодне число не може бути від'ємним і max має бути більшим, ніж min", L"Упс, помилка", MB_OK);
                break;
            }

            hWndObject2 = FindWindow(L"OBJECT2", NULL);
            if (!hWndObject2)
            {
                WinExec("Object2.exe", SW_SHOW);
                hWndObject2 = FindWindow(L"OBJECT2", NULL);
            }

            hWndObject3 = FindWindow(L"OBJECT3", NULL);
            if (!hWndObject3)
            {
                WinExec("Object3.exe", SW_SHOW);
                hWndObject3 = FindWindow(L"OBJECT3", NULL);
            }
            

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
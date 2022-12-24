#include "framework.h"
#include "vector_params.h"
#include "resource1.h"

int n, min, max;
BOOL pn, pmin, pmax;
HWND hWndObject2;

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
                MessageBox(hDlg, L"�� ����� �����, ���� �� ���� ���� �������������� �� �����, ��� �������� ����� ������.", L"���, �������", MB_OK);
                break;
            }

            if (n <= 0 || min <= 0 || max <= 0 || max <= min)
            {
                MessageBox(hDlg, L"�� �� ������ ���� ����� � ����������.\n������: ����� ����� �� ���� ���� ��'����� � max �� ���� ������, �� min", L"���, �������", MB_OK);
                break;
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
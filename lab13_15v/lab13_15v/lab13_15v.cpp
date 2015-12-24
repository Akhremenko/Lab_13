// lab13_15v.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "lab13_15v.h"
#include "winuser.h"
#include "windows.h"
#include "windowsx.h"
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int klik = 0;
HWND mass_p[7];
int x = 100;
int y = 100;
int counter = 0;
//wchar_t name[9]=L"window";
// ��������� ���������� �������, ���������� � ���� ������ ����:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���������� ��� �����.

	// ������������� ���������� �����
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB13_15V, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��������� ������������� ����������:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB13_15V));

	MSG msg;

	// ���� ��������� ���������:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//  �������: MyRegisterClass()
//  ����������: ������������ ����� ����.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB13_15V));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB13_15V);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}



//   �������: InitInstance(HINSTANCE, int)
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//   �����������:
//   � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//    ��������� � ��������� �� ����� ������� ���� ���������.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

	HWND hWnd = CreateWindow(szWindowClass, L" DOUBLE CLICK!!!", WS_OVERLAPPEDWINDOW, x, y, 400, 480, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

BOOL CreateMenuItem(HMENU hMenu, LPWSTR str,
	UINT uID, UINT wID, HMENU hSubMenu)
{
	// ��������� ��������� mi.
	MENUITEMINFO mi;
	mi.cbSize = sizeof(MENUITEMINFO);
	mi.fMask = MIIM_STATE | MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	mi.fType = MFT_STRING;
	mi.fState = MFS_ENABLED;
	mi.dwTypeData = (LPWSTR)str;
	mi.cch = sizeof(str);
	mi.wID = wID;
	mi.hSubMenu = hSubMenu; // �������� �������.
							// ��������� ����.
	return InsertMenuItem(hMenu, uID, FALSE, &mi);
}


//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//  ����������:  ������������ ��������� � ������� ����.
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// ������� ����.
	static HMENU hMainMenu;

	switch (message)
	{

	case WM_CREATE:
		// ������� ������� ����.
		hMainMenu = CreateMenu();

		// ���������� ������� � �������� ����.
		CreateMenuItem(hMainMenu, L"Klik", 0, 0, NULL);
		CreateMenuItem(hMainMenu, L"Exit", 1, 1, NULL);

		// ������������ ���� � ����.
		SetMenu(hWnd, hMainMenu);

		// �������� ������ ����.
		DrawMenuBar(hWnd);
		break;


	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// ��������� ����� � ����:
		switch (wmId)
		{
			/*case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;*/
		case 1:
			DestroyWindow(hWnd);
			break;
		case 0:
		{
			if (klik == 0) klik = 1;
			else klik = 0;
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: �������� ���� ����� ��� ����������, ������������ HDC...
		EndPaint(hWnd, &ps);
		wchar_t nname[2];
		nname[0] = counter + '0';
		nname[1] = 0;

		SetWindowText(hWnd, (LPWSTR)nname);
	}
	break;


	case WM_DESTROY:
		DestroyWindow(hWnd);

		if (counter == 0)
		{
			PostQuitMessage(0);
		};
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	case WM_CLOSE:
	{

		if (IDOK == MessageBox(hWnd, L"OK", L"Cancel",
			MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
		{

			SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			counter--;
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		if (counter <7)
		{

			mass_p[counter] = CreateWindow(szWindowClass, (LPWSTR)"window",
				WS_OVERLAPPEDWINDOW, x, y, 400, 480, NULL, NULL, hInst, NULL);
			x += 25;
			y += 25;
			ShowWindow(mass_p[counter], 1);
			counter++;
		}

	}

	break;

	case WM_MOUSEMOVE:
		if (klik == 1) {
			RECT win;
			RECT r;
			GetWindowRect(hWnd, &win);
			GetClientRect(hWnd, &r);
			MoveWindow(hWnd, win.left - 50, win.bottom - 10, r.right - 10, r.bottom - 10, true);
		}
		break;

	case  WM_CHAR:
	{

	}

	break;
	}

	return 0;
}
// ���������� ��������� ��� ���� "� ���������".
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//
//	}
//	return (INT_PTR)FALSE;
//}

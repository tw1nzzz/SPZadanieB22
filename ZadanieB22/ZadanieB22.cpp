#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#define MI_BLUE 100
#define MI_GREEN 101
#define MI_EXIT 102

HBRUSH hGreenBrush, hBrownBrush;
int sw;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hMainWnd;
	TCHAR szClassName[] = _T("menudemo");
	MSG msg;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = _T("Menu");
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot register class"), _T("Error"), MB_OK);
		return 0;
	}
	hMainWnd = CreateWindow(szClassName, _T("Zadanie B22"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}
	ShowWindow(hMainWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Гриб");
	TCHAR str1[] = _T("Целый");
	TCHAR str2[] = _T("Без шляпки");
	switch (uMsg) {
	case WM_COMMAND:
		hMenu = GetMenu(hWnd);
		switch (LOWORD(wParam))
		{
		case MI_BLUE:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_GREEN:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_EXIT:
			DestroyWindow(hWnd);
		}
		break;
	case WM_CREATE:
		hGreenBrush = CreateSolidBrush(RGB(152, 251, 152));
		hBrownBrush = CreateSolidBrush(RGB(139, 69, 19));
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, MI_BLUE, str1);
		AppendMenu(hPopupMenu, MF_STRING, MI_GREEN, str2);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (sw == 1)
		{
			FillRect(hdc, &ps.rcPaint, hGreenBrush);
			SelectBrush(hdc, hBrownBrush);
			RoundRect(hdc, 910, 490, 1010, 840, 100, 100);
			SelectBrush(hdc, hBrownBrush);
			Chord(hdc, 760, 340, 1160, 740, 1160, 540, 760, 540);
		}
		if (sw == 2)
		{
			FillRect(hdc, &ps.rcPaint, hGreenBrush);
			SelectBrush(hdc, hBrownBrush);
			RoundRect(hdc, 910, 490, 1010, 840, 100, 100);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}
#include <Windows.h>
#include <stdio.h>
#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(wcex);
	wcex.cbWndExtra = 0;
	wcex.cbClsExtra = 0;
	wcex.hbrBackground = (HBRUSH)(RGB(0, 0, 0));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = L"Chrome";
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex)) return -1;

	RECT rect = { 0, 0, 1920, 1080 };
	HWND  hWnd = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOPMOST,
		L"Chrome",
		L"",
		WS_POPUP,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd) return -1;

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	ShowWindow(hWnd, nShowCmd);


	MARGINS Margin = { -1 };
	DwmExtendFrameIntoClientArea(hWnd, &Margin);


	MSG msg{};

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (WM_QUIT != msg.message)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(1);
	}

	UnregisterClass(L"Chrome", wcex.hInstance);
	FreeConsole();
	return static_cast<int>(msg.wParam);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		InvalidateRect(hwnd, NULL, true);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
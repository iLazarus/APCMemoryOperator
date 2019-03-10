#include <Windows.h>
#include <stdio.h>
#include "utils.h"
#include <thread>

boolean bGraphicsReady = false;

utils h;


void ReadLoop() {
	while (true)
	{
		if (GetAsyncKeyState(VK_HOME) & 1)
		{
			h.RefreshOffset();
		}
		if (GetAsyncKeyState(VK_F8) & 1)
		{
			autobot = !autobot;
		}
		if (GetAsyncKeyState(VK_F5) & 1)
		{
			itemgoods = !itemgoods;
		}
		if (GetAsyncKeyState(VK_F6) & 1)
		{
			vehicle = !vehicle;
		}
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			skeltch = !skeltch;
		}
		if (GetAsyncKeyState(VK_END) & 1)
		{
			h.DebugOffset();
		}

		if (bGraphicsReady) {
			dx.Begin();
			h.ActorLoop();
			dx.End();
		}
		Sleep(1);
	}
}

void FireNow()
{
	while (true)
	{
		if (((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0 || (GetAsyncKeyState(VK_LSHIFT) & 0x8000) != 0))
		{
			h.Fire();
		}
		Sleep(20);
	}
}

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


	// dx init 
	if (!(bGraphicsReady = dx.Init(hWnd, 1920, 1080)))
	{
		printf("DX Init Failed!\r\n");
		system("pause");
		return -1;
	}
	else
	{
		printf("DX Init Sucess!\r\n");
	}
	//

	if (!h.Init())
	{
		printf("致命的错误,重开游戏后并重新运行该软件!\r\n");
		system("pause");
		return -1;
	}


	esp = true;
	itemgoods = true;
	vehicle = false;

	thread ReadActors{ ReadLoop };
	ReadActors.detach();


	thread AimShoot{ FireNow };
	AimShoot.detach();


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
		InvalidateRect(hwnd, NULL, false);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
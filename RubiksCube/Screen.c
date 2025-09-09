#pragma once
#include "Screen.h"
#include <stdio.h>

int g_nScreenIndex;
HANDLE g_hScreen[2];
COORD screenSize;

//������ ��ũ�� ���Ǵ� �Լ�
// ȭ�� ���� �ʱ�ȭ
void ScreenInit()
{
	HWND handle = GetConsoleWindow();
	// ����� 0,0 ��ǥ�� ��ġ�ϵ��� �ܼ� â �̵�, ���� �� ���� â���� ����
	SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	//ȭ�� ���� ����
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	GetLargestConsoleWindowSize(g_hScreen[0]);
	GetLargestConsoleWindowSize(g_hScreen[1]);

	//ȭ�� ũ�� ����
	screenSize.X = GetSystemMetrics(SM_CXSCREEN);
	screenSize.Y = GetSystemMetrics(SM_CYSCREEN);
	SetConsoleScreenBufferSize(g_hScreen[0], screenSize);
	SetConsoleScreenBufferSize(g_hScreen[1], screenSize);

	SMALL_RECT consoleWindow = { 0, 0, screenSize.X - 1, screenSize.Y - 1 };
	SetConsoleWindowInfo(g_hScreen[0], TRUE, &consoleWindow);
	SetConsoleWindowInfo(g_hScreen[1], TRUE, &consoleWindow);

	SetFontSize(4);

	//Ŀ�� �����
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void SetFontSize(int size)
{
	// ��Ʈ ������ ����
	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };

	// 1:1 ������ �� ��� @ ����� �� �ȿ��ڰ� ������ ��?
	cfi.dwFontSize.X = size;
	cfi.dwFontSize.Y = size * 2;

	SetCurrentConsoleFontEx(g_hScreen[0], FALSE, &cfi);
	SetCurrentConsoleFontEx(g_hScreen[1], FALSE, &cfi);
}

//ȭ�� ���� �����
void ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', screenSize.X * screenSize.Y, Coor, &dw);
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], Coor);
}

//ȭ�� ���� ��ȯ
void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;

	SetFullScreen();
	//ScreenClear();
}

//ȭ�� ���� ����
void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

//��� �Լ�
void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x * 2, y }; // ��Ʈ ������ ���� x * 2�� �ؾ��� 
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

//��� ������ ������ �����ϴ� �Լ�
void SetColor(unsigned short color)
{
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}

void SetFullScreen()
{
	//system("mode 650");

	HWND hWnd = GetConsoleWindow();

	HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
	MONITORINFOEX monitorInfo = { 0 };
	monitorInfo.cbSize = sizeof(MONITORINFOEX);
	GetMonitorInfo(hMonitor, &monitorInfo);

	//LONG_PTR windowStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
	//SetWindowLongPtr(hWnd, GWL_STYLE, windowStyle & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX));
	SetWindowPos(hWnd, NULL, 0, 0, monitorInfo.rcMonitor.right, monitorInfo.rcMonitor.bottom, SWP_DRAWFRAME);
}

void gotoxy(int x, int y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
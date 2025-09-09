#pragma once
#include "Screen.h"
#include <stdio.h>

int g_nScreenIndex;
HANDLE g_hScreen[2];
COORD screenSize;

//프레임 워크에 사용되는 함수
// 화면 버퍼 초기화
void ScreenInit()
{
	HWND handle = GetConsoleWindow();
	// 모니터 0,0 좌표에 위치하도록 콘솔 창 이동, 가장 맨 위의 창으로 변경
	SetWindowPos(handle, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	//화면 버퍼 생성
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	GetLargestConsoleWindowSize(g_hScreen[0]);
	GetLargestConsoleWindowSize(g_hScreen[1]);

	//화면 크기 변경
	screenSize.X = GetSystemMetrics(SM_CXSCREEN);
	screenSize.Y = GetSystemMetrics(SM_CYSCREEN);
	SetConsoleScreenBufferSize(g_hScreen[0], screenSize);
	SetConsoleScreenBufferSize(g_hScreen[1], screenSize);

	SMALL_RECT consoleWindow = { 0, 0, screenSize.X - 1, screenSize.Y - 1 };
	SetConsoleWindowInfo(g_hScreen[0], TRUE, &consoleWindow);
	SetConsoleWindowInfo(g_hScreen[1], TRUE, &consoleWindow);

	SetFontSize(4);

	//커서 숨기기
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void SetFontSize(int size)
{
	// 폰트 사이즈 변경
	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };

	// 1:1 비율로 할 경우 @ 빼고는 다 안예쁘게 나오는 듯?
	cfi.dwFontSize.X = size;
	cfi.dwFontSize.Y = size * 2;

	SetCurrentConsoleFontEx(g_hScreen[0], FALSE, &cfi);
	SetCurrentConsoleFontEx(g_hScreen[1], FALSE, &cfi);
}

//화면 버퍼 지우기
void ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', screenSize.X * screenSize.Y, Coor, &dw);
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], Coor);
}

//화면 버퍼 전환
void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;

	SetFullScreen();
	//ScreenClear();
}

//화면 버퍼 해제
void ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

//출력 함수
void ScreenPrint(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x * 2, y }; // 폰트 비율에 따라 x * 2를 해야함 
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

//출력 문자의 색상을 설정하는 함수
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
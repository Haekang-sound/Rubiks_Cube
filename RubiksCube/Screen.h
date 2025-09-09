#pragma once
#include <windows.h>

enum Color
{
	Black,
	DBlue, 
	DGreen,
	DCyan,
	DRed,
	DPurple,
	DYellow,
	Gray,
	DGray,
	Blue, 
	Green,
	Cyan,
	Red,
	Purple,
	Yellow,
	White
};

//프레임 워크에 사용되는 함수
// 화면 버퍼 초기화
void ScreenInit();

void SetFontSize(int size);

//화면 버퍼 지우기
void ScreenClear();

//화면 버퍼 전환
void ScreenFlipping();

//화면 버퍼 해제
void ScreenRelease();

//출력 함수
void ScreenPrint(int x, int y, char* string);

//출력 문자의 색상을 설정하는 함수
void SetColor(unsigned short color);

//커서 위치 이동
void gotoxy(int x, int y);

void SetFullScreen();
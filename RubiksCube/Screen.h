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

//������ ��ũ�� ���Ǵ� �Լ�
// ȭ�� ���� �ʱ�ȭ
void ScreenInit();

void SetFontSize(int size);

//ȭ�� ���� �����
void ScreenClear();

//ȭ�� ���� ��ȯ
void ScreenFlipping();

//ȭ�� ���� ����
void ScreenRelease();

//��� �Լ�
void ScreenPrint(int x, int y, char* string);

//��� ������ ������ �����ϴ� �Լ�
void SetColor(unsigned short color);

//Ŀ�� ��ġ �̵�
void gotoxy(int x, int y);

void SetFullScreen();
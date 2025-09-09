#pragma once

typedef struct S_Piece
{
	int color;
	int x;
	int y;
}Piece;

typedef struct S_Cube		//Cube�� ����ü ����
{
	Piece cubeArr[6][3][3];	//Piece �ڷ����� �迭 cubeArr
}Cube;

/*void SettingValueCube(Cube* cube);*/

void RotateCube(Cube* cube, char p);//p�� �Է��� Ű

// ť���Լ� ���(�ܼ� ���)													
void PrintCube(Cube* cube);
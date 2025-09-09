#pragma once

typedef struct S_Piece
{
	int color;
	int x;
	int y;
}Piece;

typedef struct S_Cube		//Cube형 구조체 정의
{
	Piece cubeArr[6][3][3];	//Piece 자료형의 배열 cubeArr
}Cube;

/*void SettingValueCube(Cube* cube);*/

void RotateCube(Cube* cube, char p);//p는 입력한 키

// 큐브함수 출력(단순 출력)													
void PrintCube(Cube* cube);
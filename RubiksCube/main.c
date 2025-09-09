#include <stdio.h>
#include "Circle.h"
#include "Screen.h"
#include <time.h>
#include "Title.h"
#include "Cube.h"
#include "SceneManager.h"
#include "3DCube.h"

//#include <fmod.h>

// const int 는 런타임에 rvalue의 값이 저장되므로 배열을 선언할 때 크기로 사용하려면 define을 사용해야함
#define numOfCircle 9 

Scene currentScene = Title; // 현재 Scene
Cube myCube;

COORD circlePoint[numOfCircle][180];
Circle circles[numOfCircle];

int compare(const void* a, const void* b)
{
// 	int tempa = (*((Intersection**)a))->theta;
// 	int tempb = (*((Intersection**)b))->theta;
	return (*((Intersection**)a))->theta - (*((Intersection**)b))->theta;
}

int isClockRoatate;

void Init()
{
	// 버퍼 생성, 화면 초기화
	ScreenInit();
	// 큐브 값 초기화
	SettingValueCube(&myCube);

	// 원 생성
	MakeCurcle(circles, circlePoint);
	// 교점 생성
	SetIntersection(&myCube, circles);
	for (int i = 0; i < numOfCircle; i++)
	{
		SetInsectionAngle(&circles[i]);
		qsort(circles[i].intersections, 12, sizeof((circles[i].intersections[0])), compare);
	}
}

void Temp()
{
	const int scale = 1;
	const int cubeLength = 5;

	double centerX = 30;
	double centerY = 30;
	double centerZ = 30;

	// 큐브
	///육면체의 중심은 30*2,30,30(x,y,z)
	Vector3 start = { centerX , centerY, -100 }; // 시작점 start point
	Vector3 eye = { 0, 0, -1 }; // 시작점 start point

	Vector3 center = { centerX , centerY, }; // 중앙좌표
	Vector3 center2 = { centerX , centerY, centerZ }; // z값 다른 중앙좌표

	COORD middlePoint = ScreenCOORD(start, center);
	COORD middlePoint2 = ScreenCOORD(start, center2);	// 다른 중앙좌표 출력용

	///현재 이미 원래 중심축을 기준으로 (현재 돌아가는 회전축) 정육면체가 형성이 됐는데
	///회전축을 바꾸려면 이미 형성된 정육면체의 좌표를 기준으로 회전축을 재정의해서 회전공식을 새로 짠다

	//	26*8의 큐브배열을 담기 위한 구조체배열 
	Vector3 cubePoint3D[27][8];

	//	큐브 3D좌표 생성후 구조체 배열에 담기
	for (int i = 5; i <= 25; i += 10) // 5, 15, 25
	{
		for (int j = 0; j < 9; j++) // 0 - 26 27번 돌거고
		{
			switch (j % 9)
			{
			case 0:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX - 12, centerY - 12, centerZ - i, scale);
				break;
			case 1:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY - 12, centerZ - i, scale);
				break;
			case 2:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY - 12, centerZ - i, scale);
				break;
			case 3:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX - 12, centerY, centerZ - i, scale);
				break;
			case 4:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY, centerZ - i, scale);
				break;
			case 5:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY, centerZ - i, scale);
				break;
			case 6:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX - 12, centerY + 12, centerZ - i, scale);
				break;
			case 7:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY + 12, centerZ - i, scale);
				break;
			case 8:
				MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY + 12, centerZ - i, scale);
				break;
			}
		}
	}

	/// 생성된 3D좌표를 2D좌표로 변환
	COORD cubePoint2D[27][8];
	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cubePoint2D[i][j] = ScreenCOORD(start, cubePoint3D[i][j]);
		}
	}

	// 후면 출력 
	Vector3 v1Front = MakeVector3D(cubePoint3D[4][6], cubePoint3D[4][7]);
	Vector3 v2Front = MakeVector3D(cubePoint3D[4][6], cubePoint3D[4][2]);
	double checkScalar1 = Dot(Cross(v1Front, v2Front), start);
// 	for (int i = 0; i <= 8; i++)
// 	{
		DrawSurface(cubePoint2D[8][7], cubePoint2D[8][2], cubePoint2D[8][6], cubePoint2D[8][3], myCube.cubeArr[2][2][0].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[7][7], cubePoint2D[7][2], cubePoint2D[7][6], cubePoint2D[7][3], myCube.cubeArr[2][2][1].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[6][7], cubePoint2D[6][2], cubePoint2D[6][6], cubePoint2D[6][3], myCube.cubeArr[2][2][2].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[5][7], cubePoint2D[5][2], cubePoint2D[5][6], cubePoint2D[5][3], myCube.cubeArr[2][1][0].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[4][7], cubePoint2D[4][2], cubePoint2D[4][6], cubePoint2D[4][3], myCube.cubeArr[2][1][1].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[3][7], cubePoint2D[3][2], cubePoint2D[3][6], cubePoint2D[3][3], myCube.cubeArr[2][1][2].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[2][7], cubePoint2D[2][2], cubePoint2D[2][6], cubePoint2D[2][3], myCube.cubeArr[2][0][0].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[1][7], cubePoint2D[1][2], cubePoint2D[1][6], cubePoint2D[1][3], myCube.cubeArr[2][0][1].color, checkScalar1); //hgcd
		DrawSurface(cubePoint2D[0][7], cubePoint2D[0][2], cubePoint2D[0][6], cubePoint2D[0][3], myCube.cubeArr[2][0][2].color, checkScalar1); //hgcd
//	}

	// 전면 출력 
	Vector3 v1Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][0]);
	Vector3 v2Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][5]);
	double checkScalar2 = Dot(Cross(v1Back, v2Back), start);

	for (int i = 0;  18 + i <= 26; i++)
	{
		DrawSurface(cubePoint2D[i+18][0], cubePoint2D[i+18][5], cubePoint2D[i+18][1], cubePoint2D[i+18][4], myCube.cubeArr[0][i/3][i%3].color, checkScalar2); //abfe
	}

	// 왼쪽 출력
	Vector3 v1Left = MakeVector3D(cubePoint3D[0][3], cubePoint3D[0][7]);
	Vector3 v2Left = MakeVector3D(cubePoint3D[0][3], cubePoint3D[0][0]);
	double checkScalar3 = Dot(Cross(v1Left, v2Left), eye);
// 	for (int i = 0; i <= 24; i += 3)
// 	{
		DrawSurface(cubePoint2D[0][0], cubePoint2D[0][7], cubePoint2D[0][3], cubePoint2D[0][4], myCube.cubeArr[3][0][0].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[3][0], cubePoint2D[3][7], cubePoint2D[3][3], cubePoint2D[3][4], myCube.cubeArr[3][1][0].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[6][0], cubePoint2D[6][7], cubePoint2D[6][3], cubePoint2D[6][4], myCube.cubeArr[3][2][0].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[9][0], cubePoint2D[9][7], cubePoint2D[9][3], cubePoint2D[9][4], myCube.cubeArr[3][0][1].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[12][0], cubePoint2D[12][7], cubePoint2D[12][3], cubePoint2D[12][4], myCube.cubeArr[3][1][1].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[15][0], cubePoint2D[15][7], cubePoint2D[15][3], cubePoint2D[15][4], myCube.cubeArr[3][2][1].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[18][0], cubePoint2D[18][7], cubePoint2D[18][3], cubePoint2D[18][4], myCube.cubeArr[3][0][2].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[21][0], cubePoint2D[21][7], cubePoint2D[21][3], cubePoint2D[21][4], myCube.cubeArr[3][1][2].color, checkScalar3); //adhe
		DrawSurface(cubePoint2D[24][0], cubePoint2D[24][7], cubePoint2D[24][3], cubePoint2D[24][4], myCube.cubeArr[3][2][2].color, checkScalar3); //adhe
		
//	}

	// 오른쪽  출력 
	Vector3 v1Right = MakeVector3D(cubePoint3D[2][2], cubePoint3D[2][1]);
	Vector3 v2Right = MakeVector3D(cubePoint3D[2][2], cubePoint3D[2][6]);
	double checkScalar4 = Dot(Cross(v1Right, v2Right), eye);
// 	for (int i = 2; i <= 27; i += 3)
// 	{
	DrawSurface(cubePoint2D[2 + 3 *0][1], cubePoint2D[2 + 3 *0][6], cubePoint2D[2 + 3 *0][2], cubePoint2D[2 + 3 *0][5], myCube.cubeArr[1][0][2].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *1][1], cubePoint2D[2 + 3 *1][6], cubePoint2D[2 + 3 *1][2], cubePoint2D[2 + 3 *1][5], myCube.cubeArr[1][1][2].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *2][1], cubePoint2D[2 + 3 *2][6], cubePoint2D[2 + 3 *2][2], cubePoint2D[2 + 3 *2][5], myCube.cubeArr[1][2][2].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *3][1], cubePoint2D[2 + 3 *3][6], cubePoint2D[2 + 3 *3][2], cubePoint2D[2 + 3 *3][5], myCube.cubeArr[1][0][1].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *4][1], cubePoint2D[2 + 3 *4][6], cubePoint2D[2 + 3 *4][2], cubePoint2D[2 + 3 *4][5], myCube.cubeArr[1][1][1].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *5][1], cubePoint2D[2 + 3 *5][6], cubePoint2D[2 + 3 *5][2], cubePoint2D[2 + 3 *5][5], myCube.cubeArr[1][2][1].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *6][1], cubePoint2D[2 + 3 *6][6], cubePoint2D[2 + 3 *6][2], cubePoint2D[2 + 3 *6][5], myCube.cubeArr[1][0][0].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *7][1], cubePoint2D[2 + 3 *7][6], cubePoint2D[2 + 3 *7][2], cubePoint2D[2 + 3 *7][5], myCube.cubeArr[1][1][0].color, checkScalar4); //bcgf	
	DrawSurface(cubePoint2D[2 + 3 *8][1], cubePoint2D[2 + 3 *8][6], cubePoint2D[2 + 3 *8][2], cubePoint2D[2 + 3 *8][5], myCube.cubeArr[1][2][0].color, checkScalar4); //bcgf	
//	}

	// 위쪽 출력
	Vector3 v1Top = MakeVector3D(cubePoint3D[2][5], cubePoint3D[2][4]);
	Vector3 v2Top = MakeVector3D(cubePoint3D[2][5], cubePoint3D[2][6]);
	double checkScalar5 = Dot(Cross(v1Top, v2Top), eye);
	for (int i = 0; i <= 2; i++)
	{
		DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7], myCube.cubeArr[4][i/9][i].color, checkScalar5); //efgh 
	}
	for (int i = 9; i <= 11; i++)
	{
		DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7], myCube.cubeArr[4][i/9][i%9].color, checkScalar5); //efgh 
	}
	for (int i = 18; i <= 20; i++)
	{
		DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7], myCube.cubeArr[4][i/9][i%9].color, checkScalar5); //efgh 
	}

	// 아래쪽 출력 
	Vector3 v1Bottom = MakeVector3D(cubePoint3D[6][1], cubePoint3D[6][2]);
	Vector3 v2Bottom = MakeVector3D(cubePoint3D[6][1], cubePoint3D[6][0]);
	double checkScalar6 = Dot(Cross(v1Bottom, v2Bottom), eye);
// 	for (int i = 6; i <= 8; i++)
// 	{
		DrawSurface(cubePoint2D[6][0], cubePoint2D[6][2], cubePoint2D[6][1], cubePoint2D[6][3], myCube.cubeArr[5][24 / 9][(24-6) %3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[7][0], cubePoint2D[7][2], cubePoint2D[7][1], cubePoint2D[7][3], myCube.cubeArr[5][25 / 9][(25-6) %3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[8][0], cubePoint2D[8][2], cubePoint2D[8][1], cubePoint2D[8][3], myCube.cubeArr[5][26 / 9][(26-6) %3].color, checkScalar6); //abcd 
//	}

// 	for (int i = 15; i <= 17; i++)
// 	{
		DrawSurface(cubePoint2D[15][0], cubePoint2D[15][2], cubePoint2D[15][1], cubePoint2D[15][3], myCube.cubeArr[5][15 / 9][(15-6) %3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[16][0], cubePoint2D[16][2], cubePoint2D[16][1], cubePoint2D[16][3], myCube.cubeArr[5][16 / 9][(16-6) %3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[17][0], cubePoint2D[17][2], cubePoint2D[17][1], cubePoint2D[17][3], myCube.cubeArr[5][17 / 9][(17-6) %3].color, checkScalar6); //abcd 
//	}
	 
// 	for (int i = 24; i <= 26; i++)
// 	{
		DrawSurface(cubePoint2D[24][0], cubePoint2D[24][2], cubePoint2D[24][1], cubePoint2D[24][3], myCube.cubeArr[5][6 / 9][(6-6) % 3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[25][0], cubePoint2D[25][2], cubePoint2D[25][1], cubePoint2D[25][3], myCube.cubeArr[5][7 / 9][(7-6) % 3].color, checkScalar6); //abcd 
		DrawSurface(cubePoint2D[26][0], cubePoint2D[26][2], cubePoint2D[26][1], cubePoint2D[26][3], myCube.cubeArr[5][8 / 9][(8-6) % 3].color, checkScalar6); //abcd 
//	}

// 	gotoxy(3, 3);
// 	printf("4번 큐브의 2번점  %lf,  %lf,  %lf", cubePoint3D[04][2].x, cubePoint3D[04][2].y, cubePoint3D[04][2].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);
// 	gotoxy(3, 4);
// 	printf("4번 큐브의 6번점  %lf,  %lf,  %lf", cubePoint3D[04][6].x, cubePoint3D[04][6].y, cubePoint3D[04][6].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);
// 	gotoxy(3, 5);
// 	printf("4번 큐브의 7번점  %lf,  %lf,  %lf", cubePoint3D[04][7].x, cubePoint3D[04][7].y, cubePoint3D[04][7].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);
// 
// 	gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// 중심점 1
// 	printf("mid point");
// 
// 	gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// 중심점 2
// 	printf("mid point222");

	//회전각 늘리기
	if (GetAsyncKeyState(VK_UP)) { X += 0.3; }
	if (GetAsyncKeyState(VK_DOWN)) { X -= 0.3; }
	if (GetAsyncKeyState(VK_LEFT)) { Y -= 0.3; }
	if (GetAsyncKeyState(VK_RIGHT)) { Y += 0.3; }
// 	if (GetAsyncKeyState(VK_RSHIFT)) { Z += 0.3; }
// 	if (GetAsyncKeyState(VK_CONTROL)) { Z -= 0.3; }
	if (GetAsyncKeyState('R')) { X = 0.0; Y = 0.0; Z = 0.0; }
	if (X >= 710) { X = 0; }
	else if (X <= -710) { X = 0; }
	if (Y >= 710) { Y = 0; }
	else if (Y <= -710) { Y = 0; }
	if (Z >= 710) { Z = 0; }
	else if (Z <= -710) { Z = 0; }
	
}

//데이터 갱신
void Update()
{
	
}

//화면 출력
void Render()
{
	switch (currentScene)
	{
	case Title:
		PrintTitle(10, 30);

		//화면 전환
		ScreenFlipping();
		ScreenClear();
		break;
	case InGame:
		// 원, 교점 그리기
		DrawCircle(circlePoint);
		for (int i = 0; i < 9; i++)
		{
			PrintCircleIntersection(circles[i]);
		}

		PrintKey();
		if (isClockRoatate)
		{
			PrintClockwise();
		}
		else
		{
			PrintAntiClockwise();
		}

		Temp();

		//화면 전환
		ScreenFlipping();
		ScreenClear();
		break;
	default:
		break;
	}
}

void RotateClockWise(int circleNumber)
{
	for (int iter = 0; iter < 3; iter++)
	{
		int* temp = circles[circleNumber].intersections[0]->color;
		for (int i = 0; i < 12; i++)
		{
			if (i == 11)
			{
				circles[circleNumber].intersections[i]->color = temp;
				break;
			}
			circles[circleNumber].intersections[i]->color = circles[circleNumber].intersections[i + 1]->color;
		}
		Render();
		Sleep(50);
	}
	int* temp9 = circles[circleNumber].intersections[9]->color;
	int* temp10 = circles[circleNumber].intersections[10]->color;
	int* temp11 = circles[circleNumber].intersections[11]->color;
	for (int i = 8; i >= 0; i--)
	{
		circles[circleNumber].intersections[i + 3]->color = circles[circleNumber].intersections[i]->color;
	}
	circles[circleNumber].intersections[0]->color = temp9;
	circles[circleNumber].intersections[1]->color = temp10;
	circles[circleNumber].intersections[2]->color = temp11;
}

void RotateAntiClockWise(int circleNumber)
{
	for (int iter = 0; iter < 3; iter++)
	{
		int* temp = circles[circleNumber].intersections[11]->color;
		for (int i = 11; i >= 0; i--)
		{
			if (i == 0)
			{
				circles[circleNumber].intersections[i]->color = temp;
				break;
			}
			circles[circleNumber].intersections[i]->color = circles[circleNumber].intersections[i - 1]->color;
		}
		Render();
		Sleep(50);
	}
	int* temp9 = circles[circleNumber].intersections[0]->color;
	int* temp10 = circles[circleNumber].intersections[1]->color;
	int* temp11 = circles[circleNumber].intersections[2]->color;
	for (int i = 0; i < 9; i++)
	{
		circles[circleNumber].intersections[i]->color = circles[circleNumber].intersections[i + 3]->color;
	}
	circles[circleNumber].intersections[9]->color = temp9;
	circles[circleNumber].intersections[10]->color = temp10;
	circles[circleNumber].intersections[11]->color = temp11;
}

int KeyManager()
{
	int isKeyPressed = 0;
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		return 1;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		switch (currentScene)
		{
		case Title:
			currentScene = InGame;
			break;
		case InGame:
			isClockRoatate = !isClockRoatate;
			break;
		default:
			break;
		}
	}
	else if (GetAsyncKeyState(0x51) & 0x8001) //Q
	{
		if (isClockRoatate)
		{
			RotateClockWise(0);
			RotateCube(&myCube, 't');
		}
		else
		{
			RotateAntiClockWise(0);
			RotateCube(&myCube, 'g');
		}
	}
	else if (GetAsyncKeyState(0x57) & 0x8001) //W
	{
		if (isClockRoatate)
		{
			RotateClockWise(1);
			RotateCube(&myCube, 'y');
		}
		else
		{
			RotateAntiClockWise(1);
			RotateCube(&myCube, 'h');
		}
	}
	else if (GetAsyncKeyState(0x45) & 0x8001) //E
	{
		if (isClockRoatate)
		{
			RotateClockWise(2);
			RotateCube(&myCube, 'u');
		}
		else
		{
			RotateAntiClockWise(2);
			RotateCube(&myCube, 'j');
		}
	}
	else if (GetAsyncKeyState(0x41) & 0x8001) //A
	{
		if (isClockRoatate)
		{
			RotateClockWise(3);
			RotateCube(&myCube, 'z');
		}
		else
		{
			RotateAntiClockWise(3);
			RotateCube(&myCube, 'm');
		}
	}
	else if (GetAsyncKeyState(0x53) & 0x8001) //S
	{
		if (isClockRoatate)
		{
			RotateClockWise(4);
			RotateCube(&myCube, 'a');
		}
		else
		{
			RotateAntiClockWise(4);
			RotateCube(&myCube, 'k');
		}
	}
	else if (GetAsyncKeyState(0x44) & 0x8001) //D
	{
		if (isClockRoatate)
		{
			RotateClockWise(5);
			RotateCube(&myCube, 'q');
		}
		else
		{
			RotateAntiClockWise(5);
			RotateCube(&myCube, 'o');
		}
	}
	else if (GetAsyncKeyState(0x5A) & 0x8001) //Z
	{
		if (isClockRoatate)
		{
			RotateClockWise(6);
			RotateCube(&myCube, 'r');
		}
		else
		{
			RotateAntiClockWise(6);
			RotateCube(&myCube, 'f');
		}
	}
	else if (GetAsyncKeyState(0x58) & 0x8001) //X
	{
		if (isClockRoatate)
		{
			RotateClockWise(7);
			RotateCube(&myCube, 'e');
		}
		else
		{
			RotateAntiClockWise(7);
			RotateCube(&myCube, 'd');
		}
	}
	else if (GetAsyncKeyState(0x43) & 0x8001) //C
	{
		if (isClockRoatate)
		{
			RotateClockWise(8);
			RotateCube(&myCube, 'w');
		}
		else
		{
			RotateAntiClockWise(8);
			RotateCube(&myCube, 's');
		}
	}

	else if (GetAsyncKeyState(VK_BACK) & 0x8001)
	{		SettingValueCube(&myCube);
	}
	return 0;
}

//해제 
void Release()
{
	ScreenRelease();
}

int main()
{
	Init();

	while (1)
	{
// 		//Update();
		if (KeyManager() == 1)
		{
			break;
		}
		Render(currentScene);
	}

	// 종료
	Release();
}

//clock_t CurTime, OldTime;
//OldTime = clock();
// 		while (1)
// 		{
// 			CurTime = clock(); //현재 시각
// 			if (CurTime - OldTime > (int)(1000 / 60))
// 			{
// 				OldTime = CurTime;
// 				break;
// 			}
// 		}

// FMOD_SYSTEM* fSystem;
// FMOD_SOUND* sound;
// 
// FMOD_RESULT result;
// FMOD_CHANNEL* channelCube;
// 
// result = FMOD_System_Create(&fSystem, FMOD_VERSION);
// result = FMOD_System_Init(fSystem, 32, FMOD_INIT_NORMAL, NULL);
// 
// result = FMOD_System_CreateSound(fSystem, "cubeSound.mp3", FMOD_DEFAULT, 0, &sound);
// 
// while (1)
// {
// 	FMOD_System_PlaySound(fSystem, sound, NULL, 0, &channelCube);
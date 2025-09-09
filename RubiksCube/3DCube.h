#pragma once
#include<stdio.h>
#include<math.h>
#include "eulerRotate.h"
#include "Screen.h"

#define M_PI       3.14159265358979323846   // pi

// 벡터 구조체
typedef struct S_Vector3
{
	double x, y, z;
}Vector3;

double X, Y, Z;	///각 회전축의 회전각
double x, y, z;	///회전연산 x,y,z값
double qw, qx, qy, qz;	///쿼터니언 벡터3개, 스칼라1개

/// 좌표를 찾는 함수
// 시선벡터와 3차원 공간의 벡터를 입력받고
// 2차원 공간에 투영된 좌표를 반환하는 함수
COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint);	//, Vector3 종점b
Vector3 MakeVector3D(Vector3 startPoint, Vector3 endPoint);
Vector3 Cross(Vector3 V1, Vector3 V2);
double Dot(Vector3 normal, Vector3 start);
void DrawLine(COORD firstPoint, COORD secondPoint, int color);
void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal);
void MakeCubePoint(Vector3* ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale);

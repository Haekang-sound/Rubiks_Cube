#pragma once
#include "Screen.h"
#include "Mathematics.h"
#include "Cube.h"
#include <math.h>

/// <summary>
/// 교점 - 좌표, 색(Cube에 있는 color 데이터를 포인터를 사용하려 가지고 있음), 각도, 회전할 때 사용하는 각도
/// </summary>
typedef struct S_Intersection
{
	COORD intersection;
	int* color;
	int theta; // x절편 벡터, 교점 벡터의 내적을 통해 구한 각도
	int destinationTheta; // 회전해야 하는 각도
}Intersection;

/// <summary>
/// 원, 중심점, 반지름, 교점 추가할 때 사용하는 인덱스, 교점(한 원당 교점은 12 개)
/// </summary>
typedef struct S_Circle
{
	COORD center; // 중심 점
	int r; // 반지름

	int intersectionIndex;
	Intersection* intersections[12];
}Circle;

void MakeCurcle(Circle* circles, COORD(*circlePoint)[180]);

void GetCirclePoint(Circle circle[], COORD(*circlePoint)[180]);
void SetCirclePoint(Circle* circle, int intersectionIndex);

void FindIntersection(Circle c1, Circle c2, COORD* intersection);
void AddIntersection(Circle* circle1, Circle* circle2, COORD intersection, int* color);
void SetIntersection(Cube* cube, Circle* circles);

/// <summary>
/// 모든 교점이 원에서 가지는 각도가 몇인지 계산해서 값 저장
/// </summary>
/// <param name="circle"></param>
void SetInsectionAngle(Circle* circle);

//---------- 출력 관련 -----------

/// <summary>
/// 미리 저장해둔 원의 점 그리기
/// </summary>
/// <param name="circlePoint">원의 점이 저장되어있는 배열</param>
void DrawCircle(COORD(*circlePoint)[180]);

/// <summary>
/// 실제 교점 출력
/// </summary>
/// <param name="intersection">출력할 교점 위치</param>
/// <param name="color">교점 색</param>
void PrintIntersection(COORD intersection, int* color);

/// <summary>
/// 원의 모든 교점을 출력
/// </summary>
/// <param name="circle"></param>
void PrintCircleIntersection(Circle circle);
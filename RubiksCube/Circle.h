#pragma once
#include "Screen.h"
#include "Mathematics.h"
#include "Cube.h"
#include <math.h>

/// <summary>
/// ���� - ��ǥ, ��(Cube�� �ִ� color �����͸� �����͸� ����Ϸ� ������ ����), ����, ȸ���� �� ����ϴ� ����
/// </summary>
typedef struct S_Intersection
{
	COORD intersection;
	int* color;
	int theta; // x���� ����, ���� ������ ������ ���� ���� ����
	int destinationTheta; // ȸ���ؾ� �ϴ� ����
}Intersection;

/// <summary>
/// ��, �߽���, ������, ���� �߰��� �� ����ϴ� �ε���, ����(�� ���� ������ 12 ��)
/// </summary>
typedef struct S_Circle
{
	COORD center; // �߽� ��
	int r; // ������

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
/// ��� ������ ������ ������ ������ ������ ����ؼ� �� ����
/// </summary>
/// <param name="circle"></param>
void SetInsectionAngle(Circle* circle);

//---------- ��� ���� -----------

/// <summary>
/// �̸� �����ص� ���� �� �׸���
/// </summary>
/// <param name="circlePoint">���� ���� ����Ǿ��ִ� �迭</param>
void DrawCircle(COORD(*circlePoint)[180]);

/// <summary>
/// ���� ���� ���
/// </summary>
/// <param name="intersection">����� ���� ��ġ</param>
/// <param name="color">���� ��</param>
void PrintIntersection(COORD intersection, int* color);

/// <summary>
/// ���� ��� ������ ���
/// </summary>
/// <param name="circle"></param>
void PrintCircleIntersection(Circle circle);
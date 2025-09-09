#pragma once
#include<stdio.h>
#include<math.h>
#include "eulerRotate.h"
#include "Screen.h"

#define M_PI       3.14159265358979323846   // pi

// ���� ����ü
typedef struct S_Vector3
{
	double x, y, z;
}Vector3;

double X, Y, Z;	///�� ȸ������ ȸ����
double x, y, z;	///ȸ������ x,y,z��
double qw, qx, qy, qz;	///���ʹϾ� ����3��, ��Į��1��

/// ��ǥ�� ã�� �Լ�
// �ü����Ϳ� 3���� ������ ���͸� �Է¹ް�
// 2���� ������ ������ ��ǥ�� ��ȯ�ϴ� �Լ�
COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint);	//, Vector3 ����b
Vector3 MakeVector3D(Vector3 startPoint, Vector3 endPoint);
Vector3 Cross(Vector3 V1, Vector3 V2);
double Dot(Vector3 normal, Vector3 start);
void DrawLine(COORD firstPoint, COORD secondPoint, int color);
void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal);
void MakeCubePoint(Vector3* ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale);

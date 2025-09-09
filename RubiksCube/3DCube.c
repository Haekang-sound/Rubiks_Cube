#include "3DCube.h"

#define M_PI       3.14159265358979323846   // pi

/// 좌표를 찾는 함수
// 시선벡터와 3차원 공간의 벡터를 입력받고
// 2차원 공간에 투영된 좌표를 반환하는 함수
COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint)	//, Vector3 종점b
{
	COORD temp = { 0,0 };
	Vector3 directionVector; // 방향벡터

	directionVector.x = endPoint.x - startPoint.x;
	directionVector.y = endPoint.y - startPoint.y;
	directionVector.z = endPoint.z - startPoint.z;

	double t;				// t = 시점, 투사면, 3D 오브젝트간 z거리 비율
	// 시점벡터z / 방향벡터z
	t = startPoint.z / directionVector.z;

	temp.X = startPoint.x - directionVector.x * t;
	temp.Y = startPoint.y - directionVector.y * t;
	return temp;
}

Vector3 MakeVector3D(Vector3 startPoint, Vector3 endPoint)
{
	Vector3 newVector = { endPoint.x - startPoint.x, endPoint.y - startPoint.y, endPoint.z - startPoint.z };
	return newVector;
}

Vector3 Cross(Vector3 V1, Vector3 V2)
{
	Vector3 normal = { V1.z * V2.y - V1.y * V2.z, V1.x * V2.z - V1.z * V2.x, V1.y * V2.x - V1.x * V2.y };
	return normal;
}

double Dot(Vector3 normal, Vector3 start)
{
	double dotScaler = normal.x * start.x + normal.y * start.y + normal.z * start.z;
	return dotScaler;
}

void DrawLine(COORD firstPoint, COORD secondPoint, int color)
{
	int xDistance = 100;
	int yDistance = 20;

	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)		// 두 점의 위치가 같을 경우 그 자리에 출력후 함수 종료
	{	///퍼스트포인트와 세컨드포인트를 잇는 코드
		SetColor(color);
		ScreenPrint(firstPoint.X + xDistance, firstPoint.Y + yDistance, "■");
		return;
	}
	else if (firstPoint.Y == secondPoint.Y)									// 두 점의 y이 같은 경우 x를 출력하는 함수를 실행
	{
		if (firstPoint.X < secondPoint.X)
		{
			for (double i = firstPoint.X; i <= secondPoint.X; i++)
			{
				SetColor(color);
				ScreenPrint(i + xDistance, firstPoint.Y + yDistance, "■");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.X; i <= firstPoint.X; i++)
			{
				SetColor(color);
				ScreenPrint(i + xDistance, firstPoint.Y + yDistance, "■");
			}
			return;
		}

	}
	else if (firstPoint.X == secondPoint.X)									// 두 점의 x값이 같은 경우 y를 출력하는 함수 실행
	{
		if (firstPoint.Y < secondPoint.Y)
		{
			for (double i = firstPoint.Y; i <= secondPoint.Y; i++)
			{
				SetColor(color);
				ScreenPrint(firstPoint.X + xDistance, i + yDistance, "■");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.Y; i <= firstPoint.Y; i++)
			{
				SetColor(color);
				ScreenPrint(firstPoint.X + xDistance, i + yDistance, "■");
			}
			return;
		}
	}
	double ratioXY = ((double)firstPoint.Y - secondPoint.Y) / ((double)firstPoint.X - secondPoint.X);
	double c = firstPoint.Y - (firstPoint.X * ratioXY);

	// 두 점의 x y좌표가 모두 다른 경우 직선의 방정식을 이용한 좌표를 출력하는 함수
	if (firstPoint.X < secondPoint.X)
	{
		for (double i = firstPoint.X; i <= secondPoint.X; i++)
		{
			SetColor(color);
			ScreenPrint(i + xDistance, ratioXY * i + c + yDistance, "■");
		}
	}
	else if (firstPoint.X > secondPoint.X)
	{
		for (double i = secondPoint.X; i <= firstPoint.X; i++)
		{
			SetColor(color);
			ScreenPrint(i + xDistance, ratioXY * i + c + yDistance, "■");
		}
	}
}

void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal)
{
	if (checkNormal < 0)
	{
		return;
	}
	// 1. startPoint부터 endPoint까지 직선의 방정식을 구한다.
	double ratioXY;

	// 2. 대각선 꼭짓점의 한 위치가 같을경우 예외처리한다.
	if (startPoint.X == endPoint.X)
	{
		DrawLine(startPoint, endPoint, color);
		return;
	}
	else if (startPoint.Y == endPoint.Y)
	{
		DrawLine(startPoint, endPoint, color);
		return;
	}
	else
	{
		//	3.  기울기를 구한다.
		ratioXY = (startPoint.Y - endPoint.Y) / ((double)startPoint.X - endPoint.X);

	}

	double c = startPoint.Y - (ratioXY * startPoint.X);
	if (startPoint.X < endPoint.X)
	{
		for (double i = startPoint.X; i <= endPoint.X; i++)
		{
			COORD crossPoint = { i , ratioXY * i + c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
	else if (endPoint.X < startPoint.X)
	{
		for (double i = endPoint.X; i <= startPoint.X; i++)
		{
			COORD crossPoint = { i, ratioXY * (i)+c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
}

void MakeCubePoint(Vector3* ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale)
{
	Vector3 temp = { calculateX(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[0] = temp;

	Vector3 temp1 = { calculateX(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y, Z - 0.3) };
	ptr[1] = temp1;

	Vector3 temp2 = { calculateX(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[2] = temp2;

	Vector3 temp3 = { calculateX(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[3] = temp3;

	Vector3 temp4 = { calculateX(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateZ(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[4] = temp4;

	Vector3 temp5 = { calculateX(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[5] = temp5;

	Vector3 temp6 = { calculateX(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[6] = temp6;

	Vector3 temp7 = { calculateX(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3),
		calculateY(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X - 0.45, Y - 0.8, Z - 0.3) };
	ptr[7] = temp7;

	return;
}
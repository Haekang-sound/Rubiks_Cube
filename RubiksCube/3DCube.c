#include "3DCube.h"

#define M_PI       3.14159265358979323846   // pi

/// ��ǥ�� ã�� �Լ�
// �ü����Ϳ� 3���� ������ ���͸� �Է¹ް�
// 2���� ������ ������ ��ǥ�� ��ȯ�ϴ� �Լ�
COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint)	//, Vector3 ����b
{
	COORD temp = { 0,0 };
	Vector3 directionVector; // ���⺤��

	directionVector.x = endPoint.x - startPoint.x;
	directionVector.y = endPoint.y - startPoint.y;
	directionVector.z = endPoint.z - startPoint.z;

	double t;				// t = ����, �����, 3D ������Ʈ�� z�Ÿ� ����
	// ��������z / ���⺤��z
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

	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)		// �� ���� ��ġ�� ���� ��� �� �ڸ��� ����� �Լ� ����
	{	///�۽�Ʈ����Ʈ�� ����������Ʈ�� �մ� �ڵ�
		SetColor(color);
		ScreenPrint(firstPoint.X + xDistance, firstPoint.Y + yDistance, "��");
		return;
	}
	else if (firstPoint.Y == secondPoint.Y)									// �� ���� y�� ���� ��� x�� ����ϴ� �Լ��� ����
	{
		if (firstPoint.X < secondPoint.X)
		{
			for (double i = firstPoint.X; i <= secondPoint.X; i++)
			{
				SetColor(color);
				ScreenPrint(i + xDistance, firstPoint.Y + yDistance, "��");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.X; i <= firstPoint.X; i++)
			{
				SetColor(color);
				ScreenPrint(i + xDistance, firstPoint.Y + yDistance, "��");
			}
			return;
		}

	}
	else if (firstPoint.X == secondPoint.X)									// �� ���� x���� ���� ��� y�� ����ϴ� �Լ� ����
	{
		if (firstPoint.Y < secondPoint.Y)
		{
			for (double i = firstPoint.Y; i <= secondPoint.Y; i++)
			{
				SetColor(color);
				ScreenPrint(firstPoint.X + xDistance, i + yDistance, "��");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.Y; i <= firstPoint.Y; i++)
			{
				SetColor(color);
				ScreenPrint(firstPoint.X + xDistance, i + yDistance, "��");
			}
			return;
		}
	}
	double ratioXY = ((double)firstPoint.Y - secondPoint.Y) / ((double)firstPoint.X - secondPoint.X);
	double c = firstPoint.Y - (firstPoint.X * ratioXY);

	// �� ���� x y��ǥ�� ��� �ٸ� ��� ������ �������� �̿��� ��ǥ�� ����ϴ� �Լ�
	if (firstPoint.X < secondPoint.X)
	{
		for (double i = firstPoint.X; i <= secondPoint.X; i++)
		{
			SetColor(color);
			ScreenPrint(i + xDistance, ratioXY * i + c + yDistance, "��");
		}
	}
	else if (firstPoint.X > secondPoint.X)
	{
		for (double i = secondPoint.X; i <= firstPoint.X; i++)
		{
			SetColor(color);
			ScreenPrint(i + xDistance, ratioXY * i + c + yDistance, "��");
		}
	}
}

void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, int color, double checkNormal)
{
	if (checkNormal < 0)
	{
		return;
	}
	// 1. startPoint���� endPoint���� ������ �������� ���Ѵ�.
	double ratioXY;

	// 2. �밢�� �������� �� ��ġ�� ������� ����ó���Ѵ�.
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
		//	3.  ���⸦ ���Ѵ�.
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
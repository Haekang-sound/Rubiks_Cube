#include<stdio.h>
#include<Windows.h>
#include<math.h>
#include "eulerRotate.h"
#define M_PI       3.14159265358979323846   // pi
// COORD�� ��ǥ��

// ���� ����ü
struct Vector3
{
	double x, y, z;
};
double X, Y, Z;	///�� ȸ������ ȸ����
double x, y, z;	///ȸ������ x,y,z��
double qw, qx, qy, qz;	///���ʹϾ� ����3��, ��Į��1��

void gotoxy(short x, short y);		// ����� ��ǥ�� Ŀ���� �Ű��ִ� �Լ�

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
	Vector3 normal = { V1.z * V2.y - V1. y* V2.z, V1.x * V2.z - V1.z * V2.x, V1.y*V2.x - V1.x*V2.y };
		return normal;
}

double Dot(Vector3 normal, Vector3 start)
{
	double dotScaler = normal.x * start.x + normal.y * start.y + normal.z * start.z;
	return dotScaler;
}


/// ���� �׸��� �Լ�
// ó�� ���� ���� �׸��� �Լ��� ������ x�� Ȥ�� y�࿡ ���� ��, 
// Ȥ�� ���� ���� ��ġ�� ���� ������ ���Ѽ� ���ڷ� �Ѱ��־�� �ߴ�.
// ������ ���� ���� ��ġ�� ������ ������� �� ���� ��ǥ�� �Ѱ��ָ�
// ���� �̾��ִ� �Լ��� �������.
// 2023-04-22 (18:30)
// ++ �� �Լ��� ���� ���� ������ �ߴ�.
// �ܼ� ȭ��� ������ �׻� x��ǥ�� 2�� ���ؼ� ǥ���ߴµ� �ƹ����� ���� ���� ���ϴٰ�
// ť�� �����ġ�� ���� ���������� ���� �Ǿ���ȴ�.
// �̰� ��ġ�µ� �ʹ� ���� �ð��� ���.
// �����.. ������.. ������ �������� �Ĳ��� �о�鼭 ������ ã��;
// 2023-04-23 (01:30)
void DrawLine(COORD firstPoint, COORD secondPoint, char color)
{
	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)		// �� ���� ��ġ�� ���� ��� �� �ڸ��� ����� �Լ� ����
	{	///�۽�Ʈ����Ʈ�� ����������Ʈ�� �մ� �ڵ�
		gotoxy(firstPoint.X, firstPoint.Y);
		printf("%c", color);
		return;
	}
	else if (firstPoint.Y == secondPoint.Y)									// �� ���� y�� ���� ��� x�� ����ϴ� �Լ��� ����
	{
		if (firstPoint.X < secondPoint.X)
		{
			for (double i = firstPoint.X; i <= secondPoint.X; i++)
			{
				gotoxy(i, firstPoint.Y);
				printf("%c",color);
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.X; i <= firstPoint.X; i++)
			{
				gotoxy(i, firstPoint.Y);
				printf("%c", color);
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
				gotoxy(firstPoint.X, i);
				printf("%c", color);
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.Y; i <= firstPoint.Y; i++)
			{
				gotoxy(firstPoint.X, i);
				printf("%c", color);
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
			gotoxy(i, ratioXY * i + c);
			printf("%c", color);
		}
	}
	else if (firstPoint.X > secondPoint.X)
	{
		for (double i = secondPoint.X; i <= firstPoint.X; i++)
		{
			gotoxy(i, ratioXY * i + c);
			printf("%c", color);
		}
	}
}



/// ���� �׸��� �Լ�
// ���� �׸��� �Լ��� ��������� ����� �ʰڴٰ� �����ߴµ�
// �����ϸ� �����Ҽ��� �׳� ������ �Լ��� �ƴѰ� ����.
/*
void DrawSurface(COORD a, COORD b, COORD c)
{
	//
	//���� ����ϱ� ���� �˾ƾ� �ϴ°�
	// 1. ������� x, y ����
	//		1)x������ �˱����� �˾ƾ� �ϴ°�
	//			>> ������� x,y��ǥ
	//				(1)������� xy��ǥ�� �˱����� �˾ƾ� �ϴ� ��
	//					�� a, b�� ������ �����İ� ����
	//
	//
	//
	// 2. ������ �����ؼ� ����ϸ� ���??
	//
	// ����4���� ������ �����ұ�?
	//
	//
	// 1. a - c���� ������ �������� ���Ѵ�.
// 	if (a.X == b.X )
// 	{
// 		if ()
// 		{
// 			a.X++;
// 		}
//
// 		a.Y++;
// 	}
	double ratioXY;
	if (a.X == b.X)
	{
		DrawLine(a, b);
		return;
	}
	else if (a.Y == b.Y)
	{
		DrawLine(a, b);
		return;
	}
	else
		ratioXY = (a.Y - b.Y) / (a.X - b.X);

	// 2. ����� ���Ѵ�
	double c1 = a.Y - (ratioXY * a.X);

	if (a.X < b.X)
	{
		for (double i = 0; a.X + i <= b.X; i++)
		{
			gotoxy(i + a.X, ratioXY * (a.X + i) + c1);
			printf("*");
			COORD crossPoint = { i + a.X, ratioXY * (a.X + i) + c1 };
			DrawLine(crossPoint, c);
		}
		return;
	}

	else if (a.X > b.X)
	{
		for (double i = 0; b.X + i <= a.X; i++)
		{
			gotoxy(i + b.X, ratioXY * (b.X + i) + c1);
			printf("*");
			COORD crossPoint = { i + a.X, ratioXY * (b.X + i) + c1 };
			DrawLine(crossPoint, c);

		}
		return;
	}
	else
		return;
}*/
// 2023-04-25 
// ���� ����ϴ� �Լ��� �ΰ� �����ߴ�.
// �Ѵ� ����� �¾����� ���� ������ ���ư��� �ʾҴ�.
// �Ǽ��� ������ ����� �� �������...
// �ƴ� ����׶� �Ĳ��� ����....
//

void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint, char color, double checkNormal)
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
			gotoxy(i, ratioXY * i + c);
			COORD crossPoint = { i , ratioXY * i + c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
	else if (endPoint.X < startPoint.X)
	{
		for (double i = endPoint.X; i <= startPoint.X; i++)
		{
			gotoxy(i + endPoint.X, ratioXY * (i)+c);
			//printf("*");
			COORD crossPoint = { i, ratioXY * (i)+c };
			DrawLine(crossPoint, topPoint, color);
			DrawLine(crossPoint, bottomPoint, color);
		}
	}
}



// ť�길���
void MakeCubePoint(Vector3*ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale)
{
	ptr[0] = { calculateX(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) };

	ptr[1] = { calculateX(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) };

	ptr[2] = { calculateX(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) };

	ptr[3] = { calculateX(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) };

	ptr[4] = { calculateX(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z),
		calculateZ(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) };

	ptr[5] = { calculateX(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 15, X, Y, Z) };

	ptr[6] = { calculateX(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX + (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) };

	ptr[7] = { calculateX(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z),
		calculateY(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) ,
		calculateZ(centerX - (cubeLength * scale) - 30, centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 15, X, Y, Z) };

	return;

}

int main(void)
{
	system("mode con cols=120 lines=60");

	while (1)
	{
		// ���� ����� 
		int screenWidth = 60;
		int screenHeight = 60;
		for (int i = 0; i < screenWidth; i++)
		{
			for (int j = 0; j < screenHeight; j++)
			{
				if (j == 0 || j == screenHeight - 1)
				{
					gotoxy(i, j);
					printf("*");
				}
				else if (i == 0 || i == screenWidth - 1)
				{
					gotoxy(i, j);
					printf("*");
				}
			}
		}

		const int scale = 1;
		const int cubeLength = 5;

		double centerX = screenWidth / 2;
		double centerY = screenHeight / 2;
		double centerZ = 30;

		// ť��
		///����ü�� �߽��� 30*2,30,30(x,y,z)
		Vector3 start = { centerX , centerY, -100 }; // ������ start point

		Vector3 center = { centerX , centerY, }; // �߾���ǥ
		Vector3 center2 = { centerX , centerY, centerZ }; // z�� �ٸ� �߾���ǥ

		COORD middlePoint = ScreenCOORD(start, center);
		COORD middlePoint2 = ScreenCOORD(start, center2);	// �ٸ� �߾���ǥ ��¿�

		///���� �̹� ���� �߽����� �������� (���� ���ư��� ȸ����) ������ü�� ������ �ƴµ�
		///ȸ������ �ٲٷ��� �̹� ������ ������ü�� ��ǥ�� �������� ȸ������ �������ؼ� ȸ�������� ���� §��


 		//	26*8�� ť��迭�� ��� ���� ����ü�迭 
		Vector3 cubePoint3D[27][8];
		
		//	ť�� 3D��ǥ ������ ����ü �迭�� ���
		for (int i = 5; i <= 25 ; i+=10) // 5, 15, 25
		{
			for (int j = 0; j < 9; j++) // 0 - 26 27�� ���Ű�
			{
				switch (j % 9)
				{
				case 0:
					MakeCubePoint(cubePoint3D[j + ((i/10) * 9)], cubeLength, centerX - 12, centerY - 12, centerZ - i, scale);
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

		/// ������ 3D��ǥ�� 2D��ǥ�� ��ȯ
		COORD cubePoint2D[27][8];
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cubePoint2D[i][j] = ScreenCOORD(start, cubePoint3D[i][j]);
			}
		}

		/// �����
// 		for(int i = 0 ; i < 27 ; i++)
// 		{
// 			DrawLine(cubePoint2D[i][0], cubePoint2D[i][1]);
// 			DrawLine(cubePoint2D[i][2], cubePoint2D[i][1]);
// 			DrawLine(cubePoint2D[i][2], cubePoint2D[i][3]);
// 			DrawLine(cubePoint2D[i][0], cubePoint2D[i][3]);
// 			DrawLine(cubePoint2D[i][4], cubePoint2D[i][5]);
// 			DrawLine(cubePoint2D[i][5], cubePoint2D[i][6]);
// 			DrawLine(cubePoint2D[i][6], cubePoint2D[i][7]);
// 			DrawLine(cubePoint2D[i][7], cubePoint2D[i][4]);
// 			DrawLine(cubePoint2D[i][4], cubePoint2D[i][0]);
// 			DrawLine(cubePoint2D[i][5], cubePoint2D[i][1]);
// 			DrawLine(cubePoint2D[i][6], cubePoint2D[i][2]);
// 			DrawLine(cubePoint2D[i][7], cubePoint2D[i][3]);
// 		}


 		/// �����
// 		for (int i = 0; i < 27; i++) 
// 		{
// 			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][2], cubePoint2D[i][1], cubePoint2D[i][3]); //abcd 
// 			DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7]); //efgh 
// 			DrawSurface(cubePoint2D[i][1], cubePoint2D[i][6], cubePoint2D[i][2], cubePoint2D[i][5]); //bcgf	
// 			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][7], cubePoint2D[i][3], cubePoint2D[i][4]); //adhe
// 			DrawSurface(cubePoint2D[i][7], cubePoint2D[i][2], cubePoint2D[i][6], cubePoint2D[i][3]); //hgcd
// 			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][5], cubePoint2D[i][1], cubePoint2D[i][4]); //abfe
// 		}

		// ���� ��� 
		Vector3 v1Front = MakeVector3D(cubePoint3D[4][6], cubePoint3D[4][7]);
		Vector3 v2Front = MakeVector3D(cubePoint3D[4][6], cubePoint3D[4][2]);
		double checkScalar1 = Dot(Cross(v1Front, v2Front), start);
		for (int i = 0; i <= 8; i++)
		{
			DrawSurface(cubePoint2D[i][7], cubePoint2D[i][2], cubePoint2D[i][6], cubePoint2D[i][3], '1', checkScalar1); //hgcd

		}

		// �ĸ� ��� 
		Vector3 v1Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][0]);
		Vector3 v2Back = MakeVector3D(cubePoint3D[18][1], cubePoint3D[18][5]);
		double checkScalar2 = Dot(Cross(v1Back, v2Back), start);

		for (int i = 18; i <= 26 ; i++)
		{ 
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][5], cubePoint2D[i][1], cubePoint2D[i][4], '3', checkScalar2); //abfe
		}
		
 		// ���� ���
		Vector3 v1Left = MakeVector3D(cubePoint3D[0][3], cubePoint3D[0][7]);
		Vector3 v2Left = MakeVector3D(cubePoint3D[0][3], cubePoint3D[0][0]);
		double checkScalar3 = Dot(Cross(v1Left, v2Left), start);
 		for (int i = 0; i <=24  ; i+=3)
		{
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][7], cubePoint2D[i][3], cubePoint2D[i][4], '4', checkScalar3); //adhe
		}

		// ������  ��� 
		Vector3 v1Right = MakeVector3D(cubePoint3D[2][2], cubePoint3D[2][1]);
		Vector3 v2Right = MakeVector3D(cubePoint3D[2][2], cubePoint3D[2][6]);
		double checkScalar4 = Dot(Cross(v1Right, v2Right), start);
		for(int i = 2; i  <= 27 ; i+=3)
		{
			DrawSurface(cubePoint2D[i][1], cubePoint2D[i][6], cubePoint2D[i][2], cubePoint2D[i][5], '2', checkScalar4); //bcgf	
		}

		// ���� ���
		Vector3 v1Top = MakeVector3D(cubePoint3D[2][5], cubePoint3D[2][4]);
		Vector3 v2Top = MakeVector3D(cubePoint3D[2][5], cubePoint3D[2][6]);
		double checkScalar5 = Dot(Cross(v1Top, v2Top), start);
		for(int i = 0; i <= 2 ; i++)
		{
			DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7],'5', checkScalar5); //efgh 
		}
		for(int i = 9; i <= 11 ; i++)
		{
			DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7],'5', checkScalar5); //efgh 
		}
		for(int i = 18; i <= 20 ; i++)
		{
			DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7], '5', checkScalar5); //efgh 
		}

 		// �Ʒ��� ��� 
		Vector3 v1Bottom = MakeVector3D (cubePoint3D[6][1], cubePoint3D[6][2]);
		Vector3 v2Bottom = MakeVector3D (cubePoint3D[6][1], cubePoint3D[6][0]);
		double checkScalar6 = Dot(Cross(v1Bottom, v2Bottom), start);
		for (int i = 6; i <= 8; i++)
		{
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][2], cubePoint2D[i][1], cubePoint2D[i][3], '6', checkScalar6); //abcd 
		}
		
		for (int i = 6+9; i <= 8+9; i++)
		{
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][2], cubePoint2D[i][1], cubePoint2D[i][3], '6', checkScalar6); //abcd 
		}
		
		for (int i = 6+18; i <= 8+18; i++)
		{
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][2], cubePoint2D[i][1], cubePoint2D[i][3], '6', checkScalar6); //abcd 
		}

// 		����, ����1, ����2, 
// 		���� 26 = ����1 - ����
// 		Vector3 v1 = { cubePoint3D[04][6].x - cubePoint3D[04][2].x, cubePoint3D[04][6].y - cubePoint3D[04][2].y, cubePoint3D[04][6].z - cubePoint3D[04][2].z }
// 		���� 67 = ����2 - ����
// 		Vector3 v = { cubePoint3D[04][6].x - cubePoint3D[04][7].x, cubePoint3D[04][6].y - cubePoint3D[04][7].y, cubePoint3D[04][7].z - cubePoint3D[04][7].z }
// 		�븻���� = ����(���� 26, ���� 67)
// 		Vector3 N = Cross(v1, v2)
// 		����(�븻����, ī�޶� ��������)
// 		double a = (N, start)


		gotoxy(3, 3);
		printf("4�� ť���� 2����  %lf,  %lf,  %lf", cubePoint3D[04][2].x, cubePoint3D[04][2].y, cubePoint3D[04][2].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);
		gotoxy(3, 4);
		printf("4�� ť���� 6����  %lf,  %lf,  %lf", cubePoint3D[04][6].x, cubePoint3D[04][6].y, cubePoint3D[04][6].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);
		gotoxy(3, 5);
		printf("4�� ť���� 7����  %lf,  %lf,  %lf", cubePoint3D[04][7].x, cubePoint3D[04][7].y, cubePoint3D[04][7].z);// , cubePoint3D[04][6], cubePoint3D[04][7]);

		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// �߽��� 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// �߽��� 2
		printf("mid point222");
		system("cls");	//����� ���� �����

		//ȸ���� �ø���
		if (GetAsyncKeyState(VK_UP)) { X += 0.3; }
		if (GetAsyncKeyState(VK_DOWN)) { X -= 0.3; }
		if (GetAsyncKeyState(VK_LEFT)) { Y -= 0.3; }
		if (GetAsyncKeyState(VK_RIGHT)) { Y += 0.3; }
		if (GetAsyncKeyState(VK_SPACE)) { Z += 0.3; }
		if (GetAsyncKeyState(VK_CONTROL)) { Z -= 0.3; }
		if (GetAsyncKeyState('R')) { X = 0; Y = 0; Z = 0; }
		if (X >= 710) { X = 0; }
		else if (X <= -710) { X = 0; }
		if (Y >= 710) { Y = 0; }
		else if (Y <= -710) { Y = 0; }
		if (Z >= 710) { Z = 0; }
		else if (Z <= -710) { Z = 0; }
	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
#include<stdio.h>
#include<Windows.h>
#include<math.h>
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
void DrawLine(COORD firstPoint, COORD secondPoint)
{
	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)		// �� ���� ��ġ�� ���� ��� �� �ڸ��� ����� �Լ� ����
	{	///�۽�Ʈ����Ʈ�� ����������Ʈ�� �մ� �ڵ�
		gotoxy(firstPoint.X, firstPoint.Y);
		printf("*");
		return;
	}
	else if (firstPoint.Y == secondPoint.Y)									// �� ���� y�� ���� ��� x�� ����ϴ� �Լ��� ����
	{
		if (firstPoint.X < secondPoint.X)
		{
			for (double i = firstPoint.X; i <= secondPoint.X; i++)
			{
				gotoxy(i, firstPoint.Y);
				printf("*");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.X; i <= firstPoint.X; i++)
			{
				gotoxy(i, firstPoint.Y);
				printf("*");
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
				printf("*");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (double i = secondPoint.Y; i <= firstPoint.Y; i++)
			{
				gotoxy(firstPoint.X, i);
				printf("*");
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
			printf("*");
		}
	}
	else if (firstPoint.X > secondPoint.X)
	{
		for (double i = secondPoint.X; i <= firstPoint.X; i++)
		{
			gotoxy(i, ratioXY * i + c);
			printf("*");
		}
	}
}

double calculateX(int i, int j, int k)	///���Ϸ�ȸ�� x��
{
	return j * sin(X) * sin(Y) * cos(Z)
		- k * cos(X) * sin(Y) * cos(Z)
		+ j * cos(X) * sin(Z)
		+ k * sin(X) * sin(Z)
		+ i * cos(Y) * cos(Z);
}
double calculateY(int i, int j, int k)	///���Ϸ�ȸ�� y��
{
	return j * cos(X) * cos(Z)
		+ k * sin(X) * cos(Z)
		- j * sin(X) * sin(Y) * sin(Z)
		+ k * cos(X) * sin(Y) * sin(Z)
		- i * cos(Y) * sin(Z);
}
double calculateZ(int i, int j, int k)	///���Ϸ�ȸ�� z��
{
	return k * cos(X) * cos(Y)
		- j * sin(X) * cos(Y)
		+ i * sin(Y);
}

double Euler_to_Quaternion(double x, double y, double z)	///���Ϸ�->���ʹϾ� ��ȯ����
{
	double cy = cos(x * M_PI / 180.0 * 0.5);
	double sy = sin(x * M_PI / 180.0 * 0.5);
	double cp = cos(y * M_PI / 180.0 * 0.5);
	double sp = sin(y * M_PI / 180.0 * 0.5);
	double cr = cos(z * M_PI / 180.0 * 0.5);
	double sr = sin(z * M_PI / 180.0 * 0.5);

	qw = cy * cp * cr + sy * sp * sr;
	qx = cy * cp * sr - sy * sp * cr;
	qy = sy * cp * sr + cy * sp * cr;
	qz = sy * cp * cr - cy * sp * sr;
	return qw, qx, qy, qz;
}

double Vector4_to_Vector3(double qw, double qx, double qy, double qz)
{
	double x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4���� ����->3���� ���� ��ȯ
	double y = 2 * (qw * qx - qy * qz);
	double z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������
	return x, y, z;
}

double calculateForSurface(double cubeX, double cubeY, double cubeZ)	///ȸ�� �� ��¸� ����
{
	x = calculateX(cubeX, cubeY, cubeZ) + 30;	///���Ϸ�ȸ�� x,y,z ����
	y = calculateY(cubeX, cubeY, cubeZ) + 30;
	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
	// 	Euler_to_Quaternion(x, y, z);	///���Ϸ�->���ʹϾ� ��ȯ
	// 	Vector4_to_Vector3(qw, qx, qy, qz);
	return x, y, z;
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

void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint)
{
	// 1. startPoint���� endPoint���� ������ �������� ���Ѵ�.
	double ratioXY;

	// 2. �밢�� �������� �� ��ġ�� ������� ����ó���Ѵ�.
	if (startPoint.X == endPoint.X)
	{
		DrawLine(startPoint, endPoint);
		return;
	}
	else if (startPoint.Y == endPoint.Y)
	{
		DrawLine(startPoint, endPoint);
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
			//printf("dddd");
			COORD crossPoint = { i , ratioXY * i + c };
			DrawLine(crossPoint, topPoint);
			DrawLine(crossPoint, bottomPoint);
		}
	}
	else if (endPoint.X < startPoint.X)
	{
		for (double i = endPoint.X; i <= startPoint.X; i++)
		{
			gotoxy(i + endPoint.X, ratioXY * (i)+c);
			//printf("*");
			COORD crossPoint = { i, ratioXY * (i)+c };
			DrawLine(crossPoint, topPoint);
			DrawLine(crossPoint, bottomPoint);
		}
	}
}



// ť�길���
void MakeCubePoint(Vector3*ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale)
{
	ptr[0] = { centerX - (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
	ptr[1] = { centerX + (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
	ptr[2] = { centerX + (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
	ptr[3] = { centerX - (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
	ptr[4] = { centerX - (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
	ptr[5] = { centerX + (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
	ptr[6] = { centerX + (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };
	ptr[7] = { centerX - (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };

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
					MakeCubePoint(cubePoint3D[j + ((i/10) * 9)], cubeLength, centerX - 12, centerY - 12, centerZ + i, scale);
					break;
				case 1:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY - 12, centerZ + i, scale);
					break;
				case 2:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY - 12, centerZ + i, scale);
					break;
				case 3:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX - 12, centerY, centerZ + i, scale);
					break;
				case 4:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY, centerZ + i, scale);
					break;
				case 5:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY, centerZ + i, scale);
					break;
				case 6:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX - 12, centerY + 12, centerZ + i, scale);
					break;
				case 7:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX, centerY + 12, centerZ + i, scale);
					break;
				case 8:
					MakeCubePoint(cubePoint3D[j + ((i / 10) * 9)], cubeLength, centerX + 12, centerY + 12, centerZ + i, scale);
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
		for(int i = 0 ; i < 27 ; i++)
		{
			DrawLine(cubePoint2D[i][0], cubePoint2D[i][1]);
			DrawLine(cubePoint2D[i][2], cubePoint2D[i][1]);
			DrawLine(cubePoint2D[i][2], cubePoint2D[i][3]);
			DrawLine(cubePoint2D[i][0], cubePoint2D[i][3]);
			DrawLine(cubePoint2D[i][4], cubePoint2D[i][5]);
			DrawLine(cubePoint2D[i][5], cubePoint2D[i][6]);
			DrawLine(cubePoint2D[i][6], cubePoint2D[i][7]);
			DrawLine(cubePoint2D[i][7], cubePoint2D[i][4]);
			DrawLine(cubePoint2D[i][4], cubePoint2D[i][0]);
			DrawLine(cubePoint2D[i][5], cubePoint2D[i][1]);
			DrawLine(cubePoint2D[i][6], cubePoint2D[i][2]);
			DrawLine(cubePoint2D[i][7], cubePoint2D[i][3]);
		}


 		/// �����
		for (int i = 0; i < 27; i++) 
		{
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][2], cubePoint2D[i][1], cubePoint2D[i][3]); //abcd 
			DrawSurface(cubePoint2D[i][4], cubePoint2D[i][6], cubePoint2D[i][5], cubePoint2D[i][7]); //efgh 
			DrawSurface(cubePoint2D[i][1], cubePoint2D[i][6], cubePoint2D[i][2], cubePoint2D[i][5]); //bcgf	
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][7], cubePoint2D[i][3], cubePoint2D[i][4]); //adhe
			DrawSurface(cubePoint2D[i][7], cubePoint2D[i][2], cubePoint2D[i][6], cubePoint2D[i][3]); //hgcd
			DrawSurface(cubePoint2D[i][0], cubePoint2D[i][5], cubePoint2D[i][1], cubePoint2D[i][4]); //abfe
		}

		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// �߽��� 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// �߽��� 2
		printf("mid point222");
		system("cls");	//����� ���� �����
	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
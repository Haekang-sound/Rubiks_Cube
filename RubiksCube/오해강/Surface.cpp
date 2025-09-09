#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
#define INTMAX_MAX        9223372036854775807i64
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
		gotoxy(4, 4);
		printf("���� : %lf\t", ratioXY);
		printf("y-y : %lf\t", startPoint.Y - endPoint.Y);
		printf("x-x : %lf", startPoint.X - startPoint.X);
	}
	// 
	// 	double ratioXY;
	// 	if (a.X == b.X)
	// 	{
	// 		//ratioXY = INTMAX_MAX;
	// 		return;
	// 	}
	// 	else
	// 		ratioXY = (a.Y - b.Y) / (a.X - b.X);
		// 2. ����� ���Ѵ� 

		// 4. y������ ���Ѵ�.
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

		const int scale = 3;
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
		// x���� ���� y���� �Ųٷ� �׷�������
		///�� ������ ��ǥ(3����)
		Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(a2.x, a2.y, a2.z);
		Vector3 a = { x,y,z };

		Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(b2.x, b2.y, b2.z);
		Vector3 b = { x,y,z };

		Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(c2.x, c2.y, c2.z);
		Vector3 c = { x,y,z };

		Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(d2.x, d2.y, d2.z);
		Vector3 d = { x,y,z };

		Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(e2.x, e2.y, e2.z);
		Vector3 e = { x,y,z };

		Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(f2.x, f2.y, f2.z);
		Vector3 f = { x,y,z };

		Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(g2.x, g2.y, g2.z);
		Vector3 g = { x,y,z };

		Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(h2.x, h2.y, h2.z);
		Vector3 h = { x,y,z };

		///�� ������ ��ġ
		COORD a1 = ScreenCOORD(start, a);
		COORD b1 = ScreenCOORD(start, b);
		COORD c1 = ScreenCOORD(start, c);
		COORD d1 = ScreenCOORD(start, d);
		COORD e1 = ScreenCOORD(start, e);
		COORD f1 = ScreenCOORD(start, f);
		COORD g1 = ScreenCOORD(start, g);
		COORD h1 = ScreenCOORD(start, h);

		// �����
		DrawLine(a1, b1);
		DrawLine(c1, d1);
		DrawLine(h1, g1);
		DrawLine(e1, f1);
		DrawLine(e1, a1);
		DrawLine(f1, b1);
		DrawLine(g1, c1);
		DrawLine(h1, d1);
		DrawLine(d1, a1);
		DrawLine(c1, b1);
		DrawLine(g1, f1);
		DrawLine(h1, e1);

		// �����
		DrawSurface(a1, c1, b1, d1);


		// �������
		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// �߽��� 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// �߽��� 2
		printf("mid point222");
		system("cls");	//����� ���� �����

		//ȸ���� �ø���
		if (GetAsyncKeyState('W')) { X += 0.1; }
		if (GetAsyncKeyState('S')) { X -= 0.1; }
		if (GetAsyncKeyState('A')) { Y -= 0.1; }
		if (GetAsyncKeyState('D')) { Y += 0.1; }
		if (GetAsyncKeyState('Q')) { Z += 0.1; }
		if (GetAsyncKeyState('E')) { Z -= 0.1; }

		if (X >= 360)
		{
			X = -360;
		}
		else if (X <= -360)
		{
			X = 360;
		}
		if (Y >= 360)
		{
			Y = -360;
		}
		else if (Y <= -360)
		{
			Y = 360;
		}
		if (Z >= 360)
		{
			Z = -360;
		}
		else if (Z <= -360)
		{
			Z = 360;
		}
		gotoxy(5, 5);
		//printf("%f, %f, %f", X, Y, Z);	//���߿� �����

		// ��ǥ��ġȮ��
		gotoxy(a1.X, a1.Y);
		printf("a ��ġ");
		gotoxy(b1.X, b1.Y);
		printf("b ��ġ");
		gotoxy(c1.X, c1.Y);
		printf("c ��ġ");
		gotoxy(d1.X, d1.Y);
		printf("d ��ġ");
		gotoxy(e1.X, e1.Y);
		printf("e ��ġ");
		gotoxy(f1.X, f1.Y);
		printf("f ��ġ");
		gotoxy(g1.X, g1.Y);
		printf("g ��ġ");
		gotoxy(h1.X, h1.Y);
		printf("h ��ġ");

	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
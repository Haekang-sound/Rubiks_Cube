#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
// COORD�� ��ǥ��

// ���� ����ü
struct Vector3
{
	float x, y, z;
};
float X, Y, Z;	///�� ȸ������ ȸ����
float x, y, z;	///ȸ������ x,y,z��
float qw, qx, qy, qz;	///���ʹϾ� ����3��, ��Į��1��
float Quat[4][4];

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

	float t;				// t = ����, �����, 3D ������Ʈ�� z�Ÿ� ����
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
			for (float i = firstPoint.X; i <= secondPoint.X; i++)
			{
				gotoxy(i, firstPoint.Y);
				printf("*");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (float i = secondPoint.X; i <= firstPoint.X; i++)
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
			for (float i = firstPoint.Y; i <= secondPoint.Y; i++)
			{
				gotoxy(firstPoint.X, i);
				printf("*");
			}
			return;
		}
		else if (firstPoint.X > secondPoint.X)
		{
			for (float i = secondPoint.Y; i <= firstPoint.Y; i++)
			{
				gotoxy(firstPoint.X, i);
				printf("*");
			}
			return;
		}
	}
	float ratioXY = ((float)firstPoint.Y - secondPoint.Y) / ((float)firstPoint.X - secondPoint.X);
	float c = firstPoint.Y - (firstPoint.X * ratioXY);

	if (firstPoint.X < secondPoint.X)										// �� ���� x y��ǥ�� ��� �ٸ� ��� ������ �������� �̿��� ��ǥ�� ����ϴ� �Լ�
	{
		for (float i = firstPoint.X; i <= secondPoint.X; i++)
		{
			gotoxy(i, ratioXY * i + c);
			printf("*");
		}
	}
	else if (firstPoint.X > secondPoint.X)
	{
		for (float i = secondPoint.X; i <= firstPoint.X; i++)
		{
			gotoxy(i, ratioXY * i + c);
			printf("*");
		}
	}
}


// float calculateX(int i, int j, int k)	///���Ϸ�ȸ�� x��
// {
// 	return j * sin(X) * sin(Y) * cos(Z)
// 		- k * cos(X) * sin(Y) * cos(Z)
// 		+ j * cos(X) * sin(Z)
// 		+ k * sin(X) * sin(Z)
// 		+ i * cos(Y) * cos(Z);
// }
// float calculateY(int i, int j, int k)	///���Ϸ�ȸ�� y��
// {
// 	return j * cos(X) * cos(Z)
// 		+ k * sin(X) * cos(Z)
// 		- j * sin(X) * sin(Y) * sin(Z)
// 		+ k * cos(X) * sin(Y) * sin(Z)
// 		- i * cos(Y) * sin(Z);
// }
// float calculateZ(int i, int j, int k)	///���Ϸ�ȸ�� z��
// {
// 	return k * cos(X) * cos(Y)
// 		- j * sin(X) * cos(Y)
// 		+ i * sin(Y);
// }

float Quaternion(float x, float y, float z)	///���ʹϾ� ����(�������� x,y,z=ȸ����)
{
	float cy = cos(x * M_PI / 180.0 * 0.5);
	float sy = sin(x * M_PI / 180.0 * 0.5);
	float cp = cos(y * M_PI / 180.0 * 0.5);
	float sp = sin(y * M_PI / 180.0 * 0.5);
	float cr = cos(z * M_PI / 180.0 * 0.5);
	float sr = sin(z * M_PI / 180.0 * 0.5);		//���Ϸ��� ���ʹϾ����� ��ȯ�ϴ� �����Ϻ�

	qw = cy * cp * cr + sy * sp * sr;
	qx = cy * cp * sr - sy * sp * cr;
	qy = sy * cp * sr + cy * sp * cr;
	qz = sy * cp * cr - cy * sp * sr;

// 	Quat[0][0] = 1 - 2 * qy * qy - 2 * qz * qz;
// 	Quat[0][1] = 2 * qy * qx - 2 * qz * qw;
// 	Quat[0][2] = 2 * qy * qw + 2 * qz * qx;
// 	Quat[0][3] = 0;
// 	Quat[1][0] = 2 * qx * qy + 2 * qw * qz;
// 	Quat[1][1] = 1 - 2 * qx * qx - 2 * qz * qz;
// 	Quat[1][2] = 2 * qz * qy - 2 * qx * qw;
// 	Quat[1][3] = 0;
// 	Quat[2][0] = 2 * qx * qz - 2 * qw * qy;
// 	Quat[2][1] = 2 * qy * qz + 2 * qw * qx;
// 	Quat[2][2] = 1 - 2 * qx * qx - 2 * qy * qy;
// 	Quat[2][3] = 0;
// 	Quat[3][0] = 0;
// 	Quat[3][1] = 0;
// 	Quat[3][2] = 0;
// 	Quat[3][3] = 1;

	return qw, qx, qy, qz;
}

// float Vector4_to_Vector3(float qw, float qx, float qy, float qz)
// {
// 	x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4����->���Ϸ�ȸ������ �纯ȯ
// 	y = 2 * (qw * qx - qy * qz);
// 	z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������
// 	return x, y, z;
// } //���������...

float calculateForSurface(float cubeX, float cubeY, float cubeZ)	///ȸ�� �� ��¸� ����
{
	// 	x = calculateX(cubeX, cubeY, cubeZ);	///���Ϸ�ȸ�� x,y,z ����
	// 	y = calculateY(cubeX, cubeY, cubeZ);
	// 	z = calculateZ(cubeX, cubeY, cubeZ);
	Quaternion(X, Y, Z);	///���ʹϾ� ���
	x = cubeX * (1 - 2 * qy * qy - 2 * qz * qz) + cubeY * (2 * qx * qy - 2 * qz * qw) + cubeZ * (2 * qx * qz + 2 * qy * qw) + 60;
	y = cubeX * (2 * qx * qy + 2 * qz * qw) + cubeY * (1 - 2 * qx * qx - 2 * qz * qz) + cubeZ * (2 * qy * qz - 2 * qx * qw) + 30;
	z = cubeX * (2 * qx * qz - 2 * qy * qw) + cubeY * (2 * qy * qz + 2 * qx * qw) + cubeZ * (1 - 2 * qx * qx - 2 * qy * qy) + 30;

	return x, y, z;
}


int main(void)
{
	system("mode con cols=120 lines=60");

	while (1)
	{
		gotoxy(3, 3);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				printf("%f ", Quat[i][j]);
			}
			printf("\n");
		}
		gotoxy(10, 10);
		printf("%f", X);
		gotoxy(10, 11);
		printf("%f", Y);
		gotoxy(10, 12);
		printf("%f", Z);
		// ���� ����� 
		int screenWidth = 60 * 2;
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

		float centerX = screenWidth / 2;
		float centerY = screenHeight / 2;
		float centerZ = 30;

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
		Vector3 a2 = { centerX - (cubeLength * scale) * 2 - 60  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(a2.x, a2.y, a2.z);
		Vector3 a = { x,y,z };

		Vector3 b2 = { centerX + (cubeLength * scale) * 2 - 60  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(b2.x, b2.y, b2.z);
		Vector3 b = { x,y,z };

		Vector3 c2 = { centerX + (cubeLength * scale) * 2 - 60  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(c2.x, c2.y, c2.z);
		Vector3 c = { x,y,z };

		Vector3 d2 = { centerX - (cubeLength * scale) * 2 - 60  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(d2.x, d2.y, d2.z);
		Vector3 d = { x,y,z };

		Vector3 e2 = { centerX - (cubeLength * scale) * 2 - 60  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(e2.x, e2.y, e2.z);
		Vector3 e = { x,y,z };

		Vector3 f2 = { centerX + (cubeLength * scale) * 2 - 60  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurface(f2.x, f2.y, f2.z);
		Vector3 f = { x,y,z };

		Vector3 g2 = { centerX + (cubeLength * scale) * 2 - 60  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(g2.x, g2.y, g2.z);
		Vector3 g = { x,y,z };

		Vector3 h2 = { centerX - (cubeLength * scale) * 2 - 60  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurface(h2.x, h2.y, h2.z);
		Vector3 h = { x,y,z };

		///�� ������ ��ġ
		COORD a1 = ScreenCOORD(start, a);
		gotoxy(a1.X, a1.Y);
		printf("*");

		COORD b1 = ScreenCOORD(start, b);
		gotoxy(b1.X, b1.Y);
		printf("*");

		COORD c1 = ScreenCOORD(start, c);
		gotoxy(c1.X, c1.Y);
		printf("*");

		COORD d1 = ScreenCOORD(start, d);
		gotoxy(d1.X, d1.Y);
		printf("*");

		COORD e1 = ScreenCOORD(start, e);
		gotoxy(e1.X, e1.Y);
		printf("*");

		COORD f1 = ScreenCOORD(start, f);
		gotoxy(f1.X, f1.Y);
		printf("*");

		COORD g1 = ScreenCOORD(start, g);
		gotoxy(g1.X, g1.Y);
		printf("*");

		COORD h1 = ScreenCOORD(start, h);
		gotoxy(h1.X, h1.Y);
		printf("*");


		// ť�� �׸���
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

		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// �߽��� 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// �߽��� 2
		printf("mid point222");
		system("cls");

		//ȸ���� �ø���
		if (GetAsyncKeyState('W'))
		{
			X += 1.0;

		}
		if (GetAsyncKeyState('S'))
		{
			X -= 1.0;

		}
		if (GetAsyncKeyState('A'))
		{
			Y -= 1.0;
		}
		if (GetAsyncKeyState('D'))
		{
			Y += 1.0;
		}
		if (GetAsyncKeyState('Q'))
		{
			Z += 1.0;
		}
		if (GetAsyncKeyState('E'))
		{
			Z -= 1.0;
		}
	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
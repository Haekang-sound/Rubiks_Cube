#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

/// <summary>
/// ���ʹϾ� ȸ���� ���� �ڵ常 �ּ�ó��
/// </summary>
float X, Y, Z;	///�� ȸ������ ȸ����
float rx = 1, ry = 1, rz = 1;
float qw, qx, qy, qz;	///���ʹϾ� ����3��, ��Į��1��
float cubeWidth = 20;
int width = 160, height = 80;
float zBuffer[160 * 160];
char buffer[160 * 160];
int backgroundASCIICode = ' ';
float distanceFromCam = 0.5;
float K1 = 40;

float incrementSpeed = 5.0;

float x, y, z;
float OutofZone;
int xp, yp;
int idx;


float calculateX(int i, int j, int k)	///���Ϸ�ȸ�� x��
{
	return j * sin(X) * sin(Y) * cos(Z)
		- k * cos(X) * sin(Y) * cos(Z)
		+ j * cos(X) * sin(Z)
		+ k * sin(X) * sin(Z)
		+ i * cos(Y) * cos(Z);
}

float calculateY(int i, int j, int k)	///���Ϸ�ȸ�� y��
{
	return j * cos(X) * cos(Z)
		+ k * sin(X) * cos(Z)
		- j * sin(X) * sin(Y) * sin(Z)
		+ k * cos(X) * sin(Y) * sin(Z)
		- i * cos(Y) * sin(Z);
}
float calculateZ(int i, int j, int k)	///���Ϸ�ȸ�� z��
{
	return k * cos(X) * cos(Y)
		- j * sin(X) * cos(Y)
		+ i * sin(Y);
}

float quater(float x, float y, float z)	///���Ϸ�->���ʹϾ� ��ȯ����
{
	float cy = cos(x * M_PI / 180.0 * 0.5);
	float sy = sin(x * M_PI / 180.0 * 0.5);
	float cp = cos(y * M_PI / 180.0 * 0.5);
	float sp = sin(y * M_PI / 180.0 * 0.5);
	float cr = cos(z * M_PI / 180.0 * 0.5);
	float sr = sin(z * M_PI / 180.0 * 0.5);

	qw = cy * cp * cr + sy * sp * sr;
	qx = cy * cp * sr - sy * sp * cr;
	qy = sy * cp * sr + cy * sp * cr;
	qz = sy * cp * cr - cy * sp * sr;
	return qw, qx, qy, qz;
}



void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch)	///ȸ�� �� ��¸� ����
{
	x = calculateX(cubeX, cubeY, cubeZ);	///���Ϸ�ȸ�� x,y,z ����
	y = calculateY(cubeX, cubeY, cubeZ);
	z = calculateZ(cubeX, cubeY, cubeZ);
	quater(x, y, z);	///���Ϸ�->���ʹϾ� ��ȯ


	x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4���� ����->3���� ���� ��ȯ
	y = 2 * (qw * qx - qy * qz);
	z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������

	// 	rx *= x;
	// 	ry *= y;
	// 	rz *= z;

	OutofZone = 1 / z;	///������ �� ����
	xp = (int)(width / 2 + K1 * OutofZone * x * 2);	///�������� ���� x�� ����
	yp = (int)(height / 2 + K1 * OutofZone * y);	///�������� ���� y�� ����

	idx = xp + yp * width;	///�������� ���� �� ����
	if (idx >= 0 && idx < width * height && OutofZone>zBuffer[idx])
	{

		if (OutofZone > zBuffer[idx])
		{

			zBuffer[idx] = OutofZone;	///���۷� ������ �� ���� ����ؼ� ������
			buffer[idx] = ch;
		}
	}

}

int main()
{

	system("mode con cols=160 lines=160");
	printf("\x1b[2J");
	while (1)
	{
		memset(buffer, backgroundASCIICode, width * height);
		memset(zBuffer, 0, width * height * 4);
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) //ť�� x�ʺ�ŭ �ݺ�
		{
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) //ť�� y�ʺ�ŭ �ݺ�
			{
				calculateForSurface(cubeX, cubeY, -cubeWidth, 'x');	//�ո�
				calculateForSurface(-cubeX, cubeY, cubeWidth, 'z');	//�޸�
				calculateForSurface(cubeWidth, cubeY, cubeX, '.');	//�����ʸ�
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '.'); //���ʸ�
				calculateForSurface(cubeX, -cubeWidth, -cubeY, '.');	//����
				calculateForSurface(cubeX, cubeWidth, cubeY, '.');	//�Ʒ���

			}
		}
		printf("%f, %f, %f, %f", qw, qx, qy, qz);
		printf("\x1b[H");
		for (int k = 0; k < width * height; k++)
		{
			putchar(k % width ? buffer[k] : 10);
		}
		if (GetAsyncKeyState('W')) { X += 0.08; }
		if (GetAsyncKeyState('S')) { X -= 0.08; }
		if (GetAsyncKeyState('A')) { Y -= 0.08; }
		if (GetAsyncKeyState('D')) { Y += 0.08; }
		if (GetAsyncKeyState('Q')) { Z += 0.08; }
		if (GetAsyncKeyState('E')) { Z -= 0.08; }

		/*Sleep(1000);*/
	}

	return 0;
}
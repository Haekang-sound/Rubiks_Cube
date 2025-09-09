#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

/// <summary>
/// 쿼터니언 회전에 사용된 코드만 주석처리
/// </summary>
float X, Y, Z;	///각 회전축의 회전각
float rx = 1, ry = 1, rz = 1;
float qw, qx, qy, qz;	///쿼터니언 벡터3개, 스칼라1개
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


float calculateX(int i, int j, int k)	///오일러회전 x값
{
	return j * sin(X) * sin(Y) * cos(Z)
		- k * cos(X) * sin(Y) * cos(Z)
		+ j * cos(X) * sin(Z)
		+ k * sin(X) * sin(Z)
		+ i * cos(Y) * cos(Z);
}

float calculateY(int i, int j, int k)	///오일러회전 y값
{
	return j * cos(X) * cos(Z)
		+ k * sin(X) * cos(Z)
		- j * sin(X) * sin(Y) * sin(Z)
		+ k * cos(X) * sin(Y) * sin(Z)
		- i * cos(Y) * sin(Z);
}
float calculateZ(int i, int j, int k)	///오일러회전 z값
{
	return k * cos(X) * cos(Y)
		- j * sin(X) * cos(Y)
		+ i * sin(Y);
}

float quater(float x, float y, float z)	///오일러->쿼터니언 변환공식
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



void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch)	///회전 후 출력면 연산
{
	x = calculateX(cubeX, cubeY, cubeZ);	///오일러회전 x,y,z 연산
	y = calculateY(cubeX, cubeY, cubeZ);
	z = calculateZ(cubeX, cubeY, cubeZ);
	quater(x, y, z);	///오일러->쿼터니언 변환


	x = 2 * (qx * qz - qw * qy);	///쿼터니언 4차원 벡터->3차원 벡터 변환
	y = 2 * (qw * qx - qy * qz);
	z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능

	// 	rx *= x;
	// 	ry *= y;
	// 	rz *= z;

	OutofZone = 1 / z;	///가려진 면 연산
	xp = (int)(width / 2 + K1 * OutofZone * x * 2);	///가려지지 않은 x축 연산
	yp = (int)(height / 2 + K1 * OutofZone * y);	///가려지지 않은 y축 연산

	idx = xp + yp * width;	///가려지지 않은 면 연산
	if (idx >= 0 && idx < width * height && OutofZone>zBuffer[idx])
	{

		if (OutofZone > zBuffer[idx])
		{

			zBuffer[idx] = OutofZone;	///버퍼로 가려진 면 먼저 출력해서 가리기
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
		for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) //큐브 x너비만큼 반복
		{
			for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += incrementSpeed) //큐브 y너비만큼 반복
			{
				calculateForSurface(cubeX, cubeY, -cubeWidth, 'x');	//앞면
				calculateForSurface(-cubeX, cubeY, cubeWidth, 'z');	//뒷면
				calculateForSurface(cubeWidth, cubeY, cubeX, '.');	//오른쪽면
				calculateForSurface(-cubeWidth, cubeY, -cubeX, '.'); //왼쪽면
				calculateForSurface(cubeX, -cubeWidth, -cubeY, '.');	//윗면
				calculateForSurface(cubeX, cubeWidth, cubeY, '.');	//아랫면

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
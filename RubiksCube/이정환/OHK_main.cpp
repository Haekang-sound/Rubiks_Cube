#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
// COORD는 좌표계

// 벡터 구조체
struct Vector3
{
	float x, y, z;
};
float X, Y, Z;	///각 회전축의 회전각
float x, y, z;	///회전연산 x,y,z값
float qw, qx, qy, qz;	///쿼터니언 벡터3개, 스칼라1개
float Quat[4][4];

void gotoxy(short x, short y);		// 출력할 좌표에 커서를 옮겨주는 함수

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

	float t;				// t = 시점, 투사면, 3D 오브젝트간 z거리 비율
	// 시점벡터z / 방향벡터z
	t = startPoint.z / directionVector.z;

	temp.X = startPoint.x - directionVector.x * t;
	temp.Y = startPoint.y - directionVector.y * t;
	return temp;
}

/// 선을 그리는 함수
// 처음 점과 점을 그리는 함수는 동일한 x축 혹은 y축에 있을 때, 
// 혹은 점과 점의 위치에 따라 순서를 지켜서 인자로 넘겨주어야 했다.
// 하지만 이제 점의 위치나 순서에 상관없이 두 점의 좌표만 넘겨주면
// 선을 이어주는 함수를 만들었다.
// 2023-04-22 (18:30)
// ++ 이 함수는 정말 나를 귀찮게 했다.
// 콘솔 화면비 때문에 항상 x좌표에 2를 곱해서 표기했는데 아무생각 없이 전부 곱하다가
// 큐브 출력위치가 전부 오른쪽으로 몰빵 되어버렸다.
// 이걸 고치는데 너무 많은 시간을 썼다.
// 디버그.. 잘하자.. 생각만 하지말고 꼼꼼히 읽어가면서 문제를 찾자;
// 2023-04-23 (01:30)
void DrawLine(COORD firstPoint, COORD secondPoint)
{
	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)		// 두 점의 위치가 같을 경우 그 자리에 출력후 함수 종료
	{	///퍼스트포인트와 세컨드포인트를 잇는 코드
		gotoxy(firstPoint.X, firstPoint.Y);
		printf("*");
		return;
	}
	else if (firstPoint.Y == secondPoint.Y)									// 두 점의 y이 같은 경우 x를 출력하는 함수를 실행
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
	else if (firstPoint.X == secondPoint.X)									// 두 점의 x값이 같은 경우 y를 출력하는 함수 실행
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

	if (firstPoint.X < secondPoint.X)										// 두 점의 x y좌표가 모두 다른 경우 직선의 방정식을 이용한 좌표를 출력하는 함수
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


// float calculateX(int i, int j, int k)	///오일러회전 x값
// {
// 	return j * sin(X) * sin(Y) * cos(Z)
// 		- k * cos(X) * sin(Y) * cos(Z)
// 		+ j * cos(X) * sin(Z)
// 		+ k * sin(X) * sin(Z)
// 		+ i * cos(Y) * cos(Z);
// }
// float calculateY(int i, int j, int k)	///오일러회전 y값
// {
// 	return j * cos(X) * cos(Z)
// 		+ k * sin(X) * cos(Z)
// 		- j * sin(X) * sin(Y) * sin(Z)
// 		+ k * cos(X) * sin(Y) * sin(Z)
// 		- i * cos(Y) * sin(Z);
// }
// float calculateZ(int i, int j, int k)	///오일러회전 z값
// {
// 	return k * cos(X) * cos(Y)
// 		- j * sin(X) * cos(Y)
// 		+ i * sin(Y);
// }

float Quaternion(float x, float y, float z)	///쿼터니언 공식(지역변수 x,y,z=회전각)
{
	float cy = cos(x * M_PI / 180.0 * 0.5);
	float sy = sin(x * M_PI / 180.0 * 0.5);
	float cp = cos(y * M_PI / 180.0 * 0.5);
	float sp = sin(y * M_PI / 180.0 * 0.5);
	float cr = cos(z * M_PI / 180.0 * 0.5);
	float sr = sin(z * M_PI / 180.0 * 0.5);		//오일러를 쿼터니언으로 변환하는 공식일부

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
// 	x = 2 * (qx * qz - qw * qy);	///쿼터니언 4벡터->오일러회전으로 재변환
// 	y = 2 * (qw * qx - qy * qz);
// 	z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능
// 	return x, y, z;
// } //쓸모없어짐...

float calculateForSurface(float cubeX, float cubeY, float cubeZ)	///회전 후 출력면 연산
{
	// 	x = calculateX(cubeX, cubeY, cubeZ);	///오일러회전 x,y,z 연산
	// 	y = calculateY(cubeX, cubeY, cubeZ);
	// 	z = calculateZ(cubeX, cubeY, cubeZ);
	Quaternion(X, Y, Z);	///쿼터니언 계산
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
		// 공간 만들기 
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

		// 큐브
		///육면체의 중심은 30*2,30,30(x,y,z)
		Vector3 start = { centerX , centerY, -100 }; // 시작점 start point

		Vector3 center = { centerX , centerY, }; // 중앙좌표
		Vector3 center2 = { centerX , centerY, centerZ }; // z값 다른 중앙좌표

		COORD middlePoint = ScreenCOORD(start, center);
		COORD middlePoint2 = ScreenCOORD(start, center2);	// 다른 중앙좌표 출력용

		///현재 이미 원래 중심축을 기준으로 (현재 돌아가는 회전축) 정육면체가 형성이 됐는데
		///회전축을 바꾸려면 이미 형성된 정육면체의 좌표를 기준으로 회전축을 재정의해서 회전공식을 새로 짠다
		// x축은 같고 y축은 거꾸로 그려져있음
		///각 꼭짓점 좌표(3차원)
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

		///각 꼭짓점 위치
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


		// 큐브 그리기
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

		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// 중심점 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// 중심점 2
		printf("mid point222");
		system("cls");

		//회전각 늘리기
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
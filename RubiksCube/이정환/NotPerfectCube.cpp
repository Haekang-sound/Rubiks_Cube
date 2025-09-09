#include<stdio.h>
#include<Windows.h>
#include<math.h>
#include"eulerRotate.h"
#define M_PI       3.14159265358979323846   // pi
// COORD는 좌표계

// 벡터 구조체
struct Vector3
{
	double x, y, z;
};
double X, Y, Z;	///각 회전축의 회전각
double x, y, z;	///회전연산 x,y,z값


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

	double t;				// t = 시점, 투사면, 3D 오브젝트간 z거리 비율
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
	else if (firstPoint.X == secondPoint.X)									// 두 점의 x값이 같은 경우 y를 출력하는 함수 실행
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

	// 두 점의 x y좌표가 모두 다른 경우 직선의 방정식을 이용한 좌표를 출력하는 함수
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



/// 면을 그리는 함수
// 선을 그리는 함수를 만들었으니 어렵지 않겠다고 생각했는데
// 생각하면 생각할수록 그냥 나오는 함수는 아닌것 같다.
/*
void DrawSurface(COORD a, COORD b, COORD c)
{
	//
	//면을 출력하기 위해 알아야 하는것
	// 1. 투사면의 x, y 선분
	//		1)x선분을 알기위해 알아야 하는것
	//			>> 투사면의 x,y좌표
	//				(1)투사면의 xy좌표를 알기위해 알아야 하는 것
	//					점 a, b의 직선의 방정식과 교점
	//
	//
	//
	// 2. 교점을 구분해서 출력하면 어떨까??
	//
	// 선분4개로 범위를 지정할까?
	//
	//
	// 1. a - c까지 직선의 방정식을 구한다.
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

	// 2. 상수를 구한다
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
// 면을 출력하는 함수를 두개 구상했다.
// 둘다 계산은 맞았지만 같은 문제로 돌아가지 않았다.
// 실수와 정수를 계산할 때 고려하자...
// 아님 디버그라도 꼼꼼히 하자....
//

void DrawSurface(COORD startPoint, COORD endPoint, COORD topPoint, COORD bottomPoint)
{
	// 1. startPoint부터 endPoint까지 직선의 방정식을 구한다.
	double ratioXY;

	// 2. 대각선 꼭짓점의 한 위치가 같을경우 예외처리한다.
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
		//	3.  기울기를 구한다.
		ratioXY = (startPoint.Y - endPoint.Y) / ((double)startPoint.X - endPoint.X);
		gotoxy(4, 4);
		printf("기울기 : %lf\t", ratioXY);
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
		// 2. 상수를 구한다 

		// 4. y절편값을 구한다.
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



// 큐브만들기
void MakeCube(Vector3* ptr, int cubeLength, double centerX, double centerY, double centerZ, const int scale)
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
		// 공간 만들기 
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
		Vector3 a2 = { centerX - (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 b2 = { centerX + (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 c2 = { centerX + (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 d2 = { centerX - (cubeLength * scale)   , centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 e2 = { centerX - (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 f2 = { centerX + (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 g2 = { centerX + (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 h2 = { centerX - (cubeLength * scale)   , centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };


		Vector3 a[8];
		Vector3 b[8];
		Vector3 c[8];

		Vector3 d[8];
		Vector3 e[8];
		Vector3 f[8];

		Vector3 g[8];
		Vector3 h[8];
		Vector3 i[8];

		Vector3 j[8];
		Vector3 k[8];
		Vector3 l[8];

		Vector3 m[8];

		Vector3 n[8];

		Vector3 o[8];
		Vector3 p[8];
		Vector3 q[8];

		Vector3 r[8];
		Vector3 s[8];
		Vector3 t[8];

		Vector3 u[8];
		Vector3 v[8];
		Vector3 w[8];

		Vector3 x[8];
		Vector3 y[8];
		Vector3 z[8];

		// 큐브 출력 1번줄
		MakeCube(a, cubeLength, centerX - 12, centerY - 12, centerZ - 5, scale);
		MakeCube(b, cubeLength, centerX, centerY - 12, centerZ - 5, scale);
		MakeCube(c, cubeLength, centerX + 12, centerY - 12, centerZ - 5, scale);

		MakeCube(d, cubeLength, centerX - 12, centerY, centerZ - 5, scale);
		MakeCube(e, cubeLength, centerX, centerY, centerZ - 5, scale);
		MakeCube(f, cubeLength, centerX + 12, centerY, centerZ - 5, scale);

		MakeCube(g, cubeLength, centerX - 12, centerY + 12, centerZ - 5, scale);
		MakeCube(h, cubeLength, centerX, centerY + 12, centerZ - 5, scale);
		MakeCube(i, cubeLength, centerX + 12, centerY + 12, centerZ - 5, scale);

		// 큐브 출력 2번줄
		MakeCube(j, cubeLength, centerX - 12, centerY - 12, centerZ - 15, scale);
		MakeCube(k, cubeLength, centerX, centerY - 12, centerZ - 15, scale);
		MakeCube(l, cubeLength, centerX + 12, centerY - 12, centerZ - 15, scale);

		MakeCube(m, cubeLength, centerX - 12, centerY, centerZ - 15, scale);

		MakeCube(n, cubeLength, centerX + 12, centerY, centerZ - 15, scale);

		MakeCube(o, cubeLength, centerX - 12, centerY + 12, centerZ - 15, scale);
		MakeCube(p, cubeLength, centerX, centerY + 12, centerZ - 15, scale);
		MakeCube(q, cubeLength, centerX + 12, centerY + 12, centerZ - 15, scale);


		// 큐브 출력 3번줄
		MakeCube(r, cubeLength, centerX - 12, centerY - 12, centerZ - 25, scale);
		MakeCube(s, cubeLength, centerX, centerY - 12, centerZ - 25, scale);
		MakeCube(t, cubeLength, centerX + 12, centerY - 12, centerZ - 25, scale);

		MakeCube(u, cubeLength, centerX - 12, centerY, centerZ - 25, scale);
		MakeCube(v, cubeLength, centerX, centerY, centerZ - 25, scale);
		MakeCube(w, cubeLength, centerX + 12, centerY, centerZ - 25, scale);

		MakeCube(x, cubeLength, centerX - 12, centerY + 12, centerZ - 25, scale);
		MakeCube(y, cubeLength, centerX, centerY + 12, centerZ - 25, scale);
		MakeCube(z, cubeLength, centerX + 12, centerY + 12, centerZ - 25, scale);


		///각 꼭짓점 위치	
		COORD a00 = ScreenCOORD(start, a[0]);
		COORD a01 = ScreenCOORD(start, a[1]);
		COORD a02 = ScreenCOORD(start, a[2]);
		COORD a03 = ScreenCOORD(start, a[3]);
		COORD a04 = ScreenCOORD(start, a[4]);
		COORD a05 = ScreenCOORD(start, a[5]);
		COORD a06 = ScreenCOORD(start, a[6]);
		COORD a07 = ScreenCOORD(start, a[7]);

		gotoxy(a00.X, a00.Y);
		printf("0번 위치");

		gotoxy(a01.X, a01.Y);
		printf("1번 위치");

		gotoxy(a02.X, a02.Y);
		printf("2번 위치");

		gotoxy(a03.X, a03.Y);
		printf("3번 위치");

		gotoxy(a04.X, a04.Y);
		printf("4번 위치");

		gotoxy(a05.X, a05.Y);
		printf("5번 위치");

		gotoxy(a06.X, a06.Y);
		printf("6번 위치");

		gotoxy(a07.X, a07.Y);
		printf("7번 위치");


		COORD b00 = ScreenCOORD(start, b[0]);
		COORD b01 = ScreenCOORD(start, b[1]);
		COORD b02 = ScreenCOORD(start, b[2]);
		COORD b03 = ScreenCOORD(start, b[3]);
		COORD b04 = ScreenCOORD(start, b[4]);
		COORD b05 = ScreenCOORD(start, b[5]);
		COORD b06 = ScreenCOORD(start, b[6]);
		COORD b07 = ScreenCOORD(start, b[7]);

		COORD c00 = ScreenCOORD(start, c[0]);
		COORD c01 = ScreenCOORD(start, c[1]);
		COORD c02 = ScreenCOORD(start, c[2]);
		COORD c03 = ScreenCOORD(start, c[3]);
		COORD c04 = ScreenCOORD(start, c[4]);
		COORD c05 = ScreenCOORD(start, c[5]);
		COORD c06 = ScreenCOORD(start, c[6]);
		COORD c07 = ScreenCOORD(start, c[7]);

		COORD d00 = ScreenCOORD(start, d[0]);
		COORD d01 = ScreenCOORD(start, d[1]);
		COORD d02 = ScreenCOORD(start, d[2]);
		COORD d03 = ScreenCOORD(start, d[3]);
		COORD d04 = ScreenCOORD(start, d[4]);
		COORD d05 = ScreenCOORD(start, d[5]);
		COORD d06 = ScreenCOORD(start, d[6]);
		COORD d07 = ScreenCOORD(start, d[7]);

		COORD e00 = ScreenCOORD(start, e[0]);
		COORD e01 = ScreenCOORD(start, e[1]);
		COORD e02 = ScreenCOORD(start, e[2]);
		COORD e03 = ScreenCOORD(start, e[3]);
		COORD e04 = ScreenCOORD(start, e[4]);
		COORD e05 = ScreenCOORD(start, e[5]);
		COORD e06 = ScreenCOORD(start, e[6]);
		COORD e07 = ScreenCOORD(start, e[7]);

		COORD f00 = ScreenCOORD(start, f[0]);
		COORD f01 = ScreenCOORD(start, f[1]);
		COORD f02 = ScreenCOORD(start, f[2]);
		COORD f03 = ScreenCOORD(start, f[3]);
		COORD f04 = ScreenCOORD(start, f[4]);
		COORD f05 = ScreenCOORD(start, f[5]);
		COORD f06 = ScreenCOORD(start, f[6]);
		COORD f07 = ScreenCOORD(start, f[7]);


		COORD g00 = ScreenCOORD(start, g[0]);
		COORD g01 = ScreenCOORD(start, g[1]);
		COORD g02 = ScreenCOORD(start, g[2]);
		COORD g03 = ScreenCOORD(start, g[3]);
		COORD g04 = ScreenCOORD(start, g[4]);
		COORD g05 = ScreenCOORD(start, g[5]);
		COORD g06 = ScreenCOORD(start, g[6]);
		COORD g07 = ScreenCOORD(start, g[7]);

		COORD h00 = ScreenCOORD(start, h[0]);
		COORD h01 = ScreenCOORD(start, h[1]);
		COORD h02 = ScreenCOORD(start, h[2]);
		COORD h03 = ScreenCOORD(start, h[3]);
		COORD h04 = ScreenCOORD(start, h[4]);
		COORD h05 = ScreenCOORD(start, h[5]);
		COORD h06 = ScreenCOORD(start, h[6]);
		COORD h07 = ScreenCOORD(start, h[7]);

		COORD i00 = ScreenCOORD(start, i[0]);
		COORD i01 = ScreenCOORD(start, i[1]);
		COORD i02 = ScreenCOORD(start, i[2]);
		COORD i03 = ScreenCOORD(start, i[3]);
		COORD i04 = ScreenCOORD(start, i[4]);
		COORD i05 = ScreenCOORD(start, i[5]);
		COORD i06 = ScreenCOORD(start, i[6]);
		COORD i07 = ScreenCOORD(start, i[7]);

		COORD j00 = ScreenCOORD(start, j[0]);
		COORD j01 = ScreenCOORD(start, j[1]);
		COORD j02 = ScreenCOORD(start, j[2]);
		COORD j03 = ScreenCOORD(start, j[3]);
		COORD j04 = ScreenCOORD(start, j[4]);
		COORD j05 = ScreenCOORD(start, j[5]);
		COORD j06 = ScreenCOORD(start, j[6]);
		COORD j07 = ScreenCOORD(start, j[7]);

		COORD k00 = ScreenCOORD(start, k[0]);
		COORD k01 = ScreenCOORD(start, k[1]);
		COORD k02 = ScreenCOORD(start, k[2]);
		COORD k03 = ScreenCOORD(start, k[3]);
		COORD k04 = ScreenCOORD(start, k[4]);
		COORD k05 = ScreenCOORD(start, k[5]);
		COORD k06 = ScreenCOORD(start, k[6]);
		COORD k07 = ScreenCOORD(start, k[7]);

		COORD l00 = ScreenCOORD(start, l[0]);
		COORD l01 = ScreenCOORD(start, l[1]);
		COORD l02 = ScreenCOORD(start, l[2]);
		COORD l03 = ScreenCOORD(start, l[3]);
		COORD l04 = ScreenCOORD(start, l[4]);
		COORD l05 = ScreenCOORD(start, l[5]);
		COORD l06 = ScreenCOORD(start, l[6]);
		COORD l07 = ScreenCOORD(start, l[7]);

		COORD m00 = ScreenCOORD(start, m[0]);
		COORD m01 = ScreenCOORD(start, m[1]);
		COORD m02 = ScreenCOORD(start, m[2]);
		COORD m03 = ScreenCOORD(start, m[3]);
		COORD m04 = ScreenCOORD(start, m[4]);
		COORD m05 = ScreenCOORD(start, m[5]);
		COORD m06 = ScreenCOORD(start, m[6]);
		COORD m07 = ScreenCOORD(start, m[7]);

		COORD n00 = ScreenCOORD(start, n[0]);
		COORD n01 = ScreenCOORD(start, n[1]);
		COORD n02 = ScreenCOORD(start, n[2]);
		COORD n03 = ScreenCOORD(start, n[3]);
		COORD n04 = ScreenCOORD(start, n[4]);
		COORD n05 = ScreenCOORD(start, n[5]);
		COORD n06 = ScreenCOORD(start, n[6]);
		COORD n07 = ScreenCOORD(start, n[7]);

		COORD o00 = ScreenCOORD(start, o[0]);
		COORD o01 = ScreenCOORD(start, o[1]);
		COORD o02 = ScreenCOORD(start, o[2]);
		COORD o03 = ScreenCOORD(start, o[3]);
		COORD o04 = ScreenCOORD(start, o[4]);
		COORD o05 = ScreenCOORD(start, o[5]);
		COORD o06 = ScreenCOORD(start, o[6]);
		COORD o07 = ScreenCOORD(start, o[7]);

		COORD p00 = ScreenCOORD(start, p[0]);
		COORD p01 = ScreenCOORD(start, p[1]);
		COORD p02 = ScreenCOORD(start, p[2]);
		COORD p03 = ScreenCOORD(start, p[3]);
		COORD p04 = ScreenCOORD(start, p[4]);
		COORD p05 = ScreenCOORD(start, p[5]);
		COORD p06 = ScreenCOORD(start, p[6]);
		COORD p07 = ScreenCOORD(start, p[7]);

		COORD q00 = ScreenCOORD(start, q[0]);
		COORD q01 = ScreenCOORD(start, q[1]);
		COORD q02 = ScreenCOORD(start, q[2]);
		COORD q03 = ScreenCOORD(start, q[3]);
		COORD q04 = ScreenCOORD(start, q[4]);
		COORD q05 = ScreenCOORD(start, q[5]);
		COORD q06 = ScreenCOORD(start, q[6]);
		COORD q07 = ScreenCOORD(start, q[7]);


		COORD r00 = ScreenCOORD(start, r[0]);
		COORD r01 = ScreenCOORD(start, r[1]);
		COORD r02 = ScreenCOORD(start, r[2]);
		COORD r03 = ScreenCOORD(start, r[3]);
		COORD r04 = ScreenCOORD(start, r[4]);
		COORD r05 = ScreenCOORD(start, r[5]);
		COORD r06 = ScreenCOORD(start, r[6]);
		COORD r07 = ScreenCOORD(start, r[7]);


		COORD s00 = ScreenCOORD(start, s[0]);
		COORD s01 = ScreenCOORD(start, s[1]);
		COORD s02 = ScreenCOORD(start, s[2]);
		COORD s03 = ScreenCOORD(start, s[3]);
		COORD s04 = ScreenCOORD(start, s[4]);
		COORD s05 = ScreenCOORD(start, s[5]);
		COORD s06 = ScreenCOORD(start, s[6]);
		COORD s07 = ScreenCOORD(start, s[7]);


		COORD t00 = ScreenCOORD(start, t[0]);
		COORD t01 = ScreenCOORD(start, t[1]);
		COORD t02 = ScreenCOORD(start, t[2]);
		COORD t03 = ScreenCOORD(start, t[3]);
		COORD t04 = ScreenCOORD(start, t[4]);
		COORD t05 = ScreenCOORD(start, t[5]);
		COORD t06 = ScreenCOORD(start, t[6]);
		COORD t07 = ScreenCOORD(start, t[7]);


		COORD u00 = ScreenCOORD(start, u[0]);
		COORD u01 = ScreenCOORD(start, u[1]);
		COORD u02 = ScreenCOORD(start, u[2]);
		COORD u03 = ScreenCOORD(start, u[3]);
		COORD u04 = ScreenCOORD(start, u[4]);
		COORD u05 = ScreenCOORD(start, u[5]);
		COORD u06 = ScreenCOORD(start, u[6]);
		COORD u07 = ScreenCOORD(start, u[7]);


		COORD v00 = ScreenCOORD(start, v[0]);
		COORD v01 = ScreenCOORD(start, v[1]);
		COORD v02 = ScreenCOORD(start, v[2]);
		COORD v03 = ScreenCOORD(start, v[3]);
		COORD v04 = ScreenCOORD(start, v[4]);
		COORD v05 = ScreenCOORD(start, v[5]);
		COORD v06 = ScreenCOORD(start, v[6]);
		COORD v07 = ScreenCOORD(start, v[7]);


		COORD w00 = ScreenCOORD(start, w[0]);
		COORD w01 = ScreenCOORD(start, w[1]);
		COORD w02 = ScreenCOORD(start, w[2]);
		COORD w03 = ScreenCOORD(start, w[3]);
		COORD w04 = ScreenCOORD(start, w[4]);
		COORD w05 = ScreenCOORD(start, w[5]);
		COORD w06 = ScreenCOORD(start, w[6]);
		COORD w07 = ScreenCOORD(start, w[7]);


		COORD x00 = ScreenCOORD(start, x[0]);
		COORD x01 = ScreenCOORD(start, x[1]);
		COORD x02 = ScreenCOORD(start, x[2]);
		COORD x03 = ScreenCOORD(start, x[3]);
		COORD x04 = ScreenCOORD(start, x[4]);
		COORD x05 = ScreenCOORD(start, x[5]);
		COORD x06 = ScreenCOORD(start, x[6]);
		COORD x07 = ScreenCOORD(start, x[7]);


		COORD y00 = ScreenCOORD(start, y[0]);
		COORD y01 = ScreenCOORD(start, y[1]);
		COORD y02 = ScreenCOORD(start, y[2]);
		COORD y03 = ScreenCOORD(start, y[3]);
		COORD y04 = ScreenCOORD(start, y[4]);
		COORD y05 = ScreenCOORD(start, y[5]);
		COORD y06 = ScreenCOORD(start, y[6]);
		COORD y07 = ScreenCOORD(start, y[7]);


		COORD z00 = ScreenCOORD(start, z[0]);
		COORD z01 = ScreenCOORD(start, z[1]);
		COORD z02 = ScreenCOORD(start, z[2]);
		COORD z03 = ScreenCOORD(start, z[3]);
		COORD z04 = ScreenCOORD(start, z[4]);
		COORD z05 = ScreenCOORD(start, z[5]);
		COORD z06 = ScreenCOORD(start, z[6]);
		COORD z07 = ScreenCOORD(start, z[7]);



		// 선출력
		DrawLine(a00, a01);
		DrawLine(a02, a01);
		DrawLine(a02, a03);
		DrawLine(a00, a03);
 		DrawLine(a04, a05);
 		DrawLine(a05, a06);
 		DrawLine(a06, a07);
 		DrawLine(a07, a04);
		DrawLine(a04, a00);
		DrawLine(a05, a01);
		DrawLine(a06, a02);
		DrawLine(a07, a03);
// 
		DrawLine(b00, b01);
		DrawLine(b02, b01);
		DrawLine(b02, b03);
		DrawLine(b00, b03);
		DrawLine(b04, b05);
		DrawLine(b05, b06);
		DrawLine(b06, b07);
		DrawLine(b07, b04);
		DrawLine(b04, b00);
		DrawLine(b05, b01);
		DrawLine(b06, b02);
		DrawLine(b07, b03);

		DrawLine(c00, c01);
		DrawLine(c02, c01);
		DrawLine(c02, c03);
		DrawLine(c00, c03);
		DrawLine(c04, c05);
		DrawLine(c05, c06);
		DrawLine(c06, c07);
		DrawLine(c07, c04);
		DrawLine(c04, c00);
		DrawLine(c05, c01);
		DrawLine(c06, c02);
		DrawLine(c07, c03);

		DrawLine(d00, d01);
		DrawLine(d02, d01);
		DrawLine(d02, d03);
		DrawLine(d00, d03);
		DrawLine(d04, d05);
		DrawLine(d05, d06);
		DrawLine(d06, d07);
		DrawLine(d07, d04);
		DrawLine(d04, d00);
		DrawLine(d05, d01);
		DrawLine(d06, d02);
		DrawLine(d07, d03);

		DrawLine(e00, e01);
		DrawLine(e02, e01);
		DrawLine(e02, e03);
		DrawLine(e00, e03);
		DrawLine(e04, e05);
		DrawLine(e05, e06);
		DrawLine(e06, e07);
		DrawLine(e07, e04);
		DrawLine(e04, e00);
		DrawLine(e05, e01);
		DrawLine(e06, e02);
		DrawLine(e07, e03);

		DrawLine(f00, f01);
		DrawLine(f02, f01);
		DrawLine(f02, f03);
		DrawLine(f00, f03);
		DrawLine(f04, f05);
		DrawLine(f05, f06);
		DrawLine(f06, f07);
		DrawLine(f07, f04);
		DrawLine(f04, f00);
		DrawLine(f05, f01);
		DrawLine(f06, f02);
		DrawLine(f07, f03);

		DrawLine(g00, g01);
		DrawLine(g02, g01);
		DrawLine(g02, g03);
		DrawLine(g00, g03);
		DrawLine(g04, g05);
		DrawLine(g05, g06);
		DrawLine(g06, g07);
		DrawLine(g07, g04);
		DrawLine(g04, g00);
		DrawLine(g05, g01);
		DrawLine(g06, g02);
		DrawLine(g07, g03);

		DrawLine(h00, h01);
		DrawLine(h02, h01);
		DrawLine(h02, h03);
		DrawLine(h00, h03);
		DrawLine(h04, h05);
		DrawLine(h05, h06);
		DrawLine(h06, h07);
		DrawLine(h07, h04);
		DrawLine(h04, h00);
		DrawLine(h05, h01);
		DrawLine(h06, h02);
		DrawLine(h07, h03);

		DrawLine(i00, i01);
		DrawLine(i02, i01);
		DrawLine(i02, i03);
		DrawLine(i00, i03);
		DrawLine(i04, i05);
		DrawLine(i05, i06);
		DrawLine(i06, i07);
		DrawLine(i07, i04);
		DrawLine(i04, i00);
		DrawLine(i05, i01);
		DrawLine(i06, i02);
		DrawLine(i07, i03);

		DrawLine(j00, j01);	
		DrawLine(j02, j01);
		DrawLine(j02, j03);
		DrawLine(j00, j03);
		DrawLine(j04, j05);
		DrawLine(j05, j06);
		DrawLine(j06, j07);
		DrawLine(j07, j04);
		DrawLine(j04, j00);
		DrawLine(j05, j01);
		DrawLine(j06, j02);
		DrawLine(j07, j03);

		DrawLine(k00, k01);	
		DrawLine(k02, k01);
		DrawLine(k02, k03);
		DrawLine(k00, k03);
		DrawLine(k04, k05);
		DrawLine(k05, k06);
		DrawLine(k06, k07);
		DrawLine(k07, k04);
		DrawLine(k04, k00);
		DrawLine(k05, k01);
		DrawLine(k06, k02);
		DrawLine(k07, k03);

		DrawLine(l00, l01);	
		DrawLine(l02, l01);
		DrawLine(l02, l03);
		DrawLine(l00, l03);
		DrawLine(l04, l05);
		DrawLine(l05, l06);
		DrawLine(l06, l07);
		DrawLine(l07, l04);
		DrawLine(l04, l00);
		DrawLine(l05, l01);
		DrawLine(l06, l02);
		DrawLine(l07, l03);

		DrawLine(m00, m01);	
		DrawLine(m02, m01);
		DrawLine(m02, m03);
		DrawLine(m00, m03);
		DrawLine(m04, m05);
		DrawLine(m05, m06);
		DrawLine(m06, m07);
		DrawLine(m07, m04);
		DrawLine(m04, m00);
		DrawLine(m05, m01);
		DrawLine(m06, m02);
		DrawLine(m07, m03);

		DrawLine(n00, n01);	
		DrawLine(n02, n01);
		DrawLine(n02, n03);
		DrawLine(n00, n03);
		DrawLine(n04, n05);
		DrawLine(n05, n06);
		DrawLine(n06, n07);
		DrawLine(n07, n04);
		DrawLine(n04, n00);
		DrawLine(n05, n01);
		DrawLine(n06, n02);
		DrawLine(n07, n03);

		DrawLine(o00, o01);
		DrawLine(o02, o01);
		DrawLine(o02, o03);
		DrawLine(o00, o03);
		DrawLine(o04, o05);
		DrawLine(o05, o06);
		DrawLine(o06, o07);
		DrawLine(o07, o04);
		DrawLine(o04, o00);
		DrawLine(o05, o01);
		DrawLine(o06, o02);
		DrawLine(o07, o03);

		DrawLine(p00, p01);	
		DrawLine(p02, p01);
		DrawLine(p02, p03);
		DrawLine(p00, p03);
		DrawLine(p04, p05);
		DrawLine(p05, p06);
		DrawLine(p06, p07);
		DrawLine(p07, p04);
		DrawLine(p04, p00);
		DrawLine(p05, p01);
		DrawLine(p06, p02);
		DrawLine(p07, p03);

		DrawLine(q00, q01);
		DrawLine(q02, q01);
		DrawLine(q02, q03);
		DrawLine(q00, q03);
		DrawLine(q04, q05);
		DrawLine(q05, q06);
		DrawLine(q06, q07);
		DrawLine(q07, q04);
		DrawLine(q04, q00);
		DrawLine(q05, q01);
		DrawLine(q06, q02);
		DrawLine(q07, q03);


		DrawLine(r00, r01);
		DrawLine(r02, r01);
		DrawLine(r02, r03);
		DrawLine(r00, r03);
		DrawLine(r04, r05);
		DrawLine(r05, r06);
		DrawLine(r06, r07);
		DrawLine(r07, r04);
		DrawLine(r04, r00);
		DrawLine(r05, r01);
		DrawLine(r06, r02);
		DrawLine(r07, r03);


		DrawLine(s00, s01);
		DrawLine(s02, s01);
		DrawLine(s02, s03);
		DrawLine(s00, s03);
		DrawLine(s04, s05);
		DrawLine(s05, s06);
		DrawLine(s06, s07);
		DrawLine(s07, s04);
		DrawLine(s04, s00);
		DrawLine(s05, s01);
		DrawLine(s06, s02);
		DrawLine(s07, s03);


		DrawLine(t00, t01);
		DrawLine(t02, t01);
		DrawLine(t02, t03);
		DrawLine(t00, t03);
		DrawLine(t04, t05);
		DrawLine(t05, t06);
		DrawLine(t06, t07);
		DrawLine(t07, t04);
		DrawLine(t04, t00);
		DrawLine(t05, t01);
		DrawLine(t06, t02);
		DrawLine(t07, t03);


		DrawLine(u00, u01);
		DrawLine(u02, u01);
		DrawLine(u02, u03);
		DrawLine(u00, u03);
		DrawLine(u04, u05);
		DrawLine(u05, u06);
		DrawLine(u06, u07);
		DrawLine(u07, u04);
		DrawLine(u04, u00);
		DrawLine(u05, u01);
		DrawLine(u06, u02);
		DrawLine(u07, u03);


		DrawLine(v00, v01);
		DrawLine(v02, v01);
		DrawLine(v02, v03);
		DrawLine(v00, v03);
		DrawLine(v04, v05);
		DrawLine(v05, v06);
		DrawLine(v06, v07);
		DrawLine(v07, v04);
		DrawLine(v04, v00);
		DrawLine(v05, v01);
		DrawLine(v06, v02);
		DrawLine(v07, v03);


		DrawLine(w00, w01);
		DrawLine(w02, w01);
		DrawLine(w02, w03);
		DrawLine(w00, w03);
		DrawLine(w04, w05);
		DrawLine(w05, w06);
		DrawLine(w06, w07);
		DrawLine(w07, w04);
		DrawLine(w04, w00);
		DrawLine(w05, w01);
		DrawLine(w06, w02);
		DrawLine(w07, w03);


		DrawLine(x00, x01);
		DrawLine(x02, x02);
		DrawLine(x02, x03);
		DrawLine(x00, x00);
		DrawLine(x04, x05);
		DrawLine(x05, x06);
		DrawLine(x06, x07);
		DrawLine(x07, x00);
		DrawLine(x04, x04);
		DrawLine(x05, x05);
		DrawLine(x06, x06);
		DrawLine(x07, x07);


		DrawLine(y00, y01);
		DrawLine(y02, y02);
		DrawLine(y02, y03);
		DrawLine(y00, y00);
		DrawLine(y04, y05);
		DrawLine(y05, y06);
		DrawLine(y06, y07);
		DrawLine(y07, y00);
		DrawLine(y04, y04);
		DrawLine(y05, y05);
		DrawLine(y06, y06);
		DrawLine(y07, y07);


		DrawLine(z00, z01);
		DrawLine(z02, z02);
		DrawLine(z02, z03);
		DrawLine(z00, z00);
		DrawLine(z04, z05);
		DrawLine(z05, z06);
		DrawLine(z06, z07);
		DrawLine(z07, z00);
		DrawLine(z04, z04);
		DrawLine(z05, z05);
		DrawLine(z06, z06);
		DrawLine(z07, z07);





		///각 꼭짓점 위치				  
// 		COORD a1 = ScreenCOORD(start, a2);
// 		COORD b1 = ScreenCOORD(start, b2);
// 		COORD c1 = ScreenCOORD(start, c2);
// 		COORD d1 = ScreenCOORD(start, d2);
// 		COORD e1 = ScreenCOORD(start, e2);
// 		COORD f1 = ScreenCOORD(start, f2);
// 		COORD g1 = ScreenCOORD(start, g2);
// 		COORD h1 = ScreenCOORD(start, h2);
// 
// 		// 선출력
// 		DrawLine(a1, b1);
// 		DrawLine(c1, d1);
// 		DrawLine(h1, g1);
// 		DrawLine(e1, f1);
// 		DrawLine(e1, a1);
// 		DrawLine(f1, b1);
// 		DrawLine(g1, c1);
// 		DrawLine(h1, d1);
// 		DrawLine(d1, a1);
// 		DrawLine(c1, b1);
// 		DrawLine(g1, f1);
// 		DrawLine(h1, e1);

		// 면출력
//  		DrawSurface(a1, c1, b1, d1); //abcd
//  		DrawSurface(e1, g1, f1, h1); //efgh
//  		DrawSurface(b1, g1, c1, f1); //bcgf
//  		DrawSurface(a1, h1, d1, e1); //adhe
//  		DrawSurface(h1, c1, g1, d1); //hgcd
//  		DrawSurface(a1, f1, b1, e1); //abfe


		// 중점출력
		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// 중심점 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// 중심점 2
		printf("mid point222");
		system("cls");	//출력한 문자 지우기

		//회전각 늘리기
		if (GetAsyncKeyState(VK_UP)) { X += 177.5; Sleep(100); }
		if (GetAsyncKeyState(VK_DOWN)) { X -= 177.5; Sleep(100); }
		if (GetAsyncKeyState(VK_LEFT)) { Y -= 177.5; Sleep(100); }
		if (GetAsyncKeyState(VK_RIGHT)) { Y += 177.5; Sleep(100); }
		if (GetAsyncKeyState(VK_SPACE)) { Z += 177.5; Sleep(100); }
		if (GetAsyncKeyState(VK_CONTROL)) { Z -= 177.5; Sleep(100); }
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
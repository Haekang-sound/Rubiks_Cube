#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
#define INTMAX_MAX        9223372036854775807i64
// COORD는 좌표계




// 벡터 구조체
struct Vector3
{
	double x, y, z;
};
double X, Y, Z;	///각 회전축의 회전각
double x, y, z;	///회전연산 x,y,z값
double qw, qx, qy, qz;	///쿼터니언 벡터3개, 스칼라1개

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


double calculateX(int i, int j, int k)	///오일러회전 x값
{
	return j * sin(X) * sin(Y) * cos(Z)
		- k * cos(X) * sin(Y) * cos(Z)
		+ j * cos(X) * sin(Z)
		+ k * sin(X) * sin(Z)
		+ i * cos(Y) * cos(Z);
}
double calculateY(int i, int j, int k)	///오일러회전 y값
{
	return j * cos(X) * cos(Z)
		+ k * sin(X) * cos(Z)
		- j * sin(X) * sin(Y) * sin(Z)
		+ k * cos(X) * sin(Y) * sin(Z)
		- i * cos(Y) * sin(Z);
}
double calculateZ(int i, int j, int k)	///오일러회전 z값
{
	return k * cos(X) * cos(Y)
		- j * sin(X) * cos(Y)
		+ i * sin(Y);
}

double Euler_to_Quaternion(double x, double y, double z)	///오일러->쿼터니언 변환공식
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
	double x = 2 * (qx * qz - qw * qy);	///쿼터니언 4차원 벡터->3차원 벡터 변환
	double y = 2 * (qw * qx - qy * qz);
	double z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능
	return x, y, z;
}

double calculateForSurface(double cubeX, double cubeY, double cubeZ)	///회전 후 출력면 연산
{
	x = calculateX(cubeX, cubeY, cubeZ) + 30;	///오일러회전 x,y,z 연산
	y = calculateY(cubeX, cubeY, cubeZ) + 30;
	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
	// 	Euler_to_Quaternion(x, y, z);	///오일러->쿼터니언 변환
	// 	Vector4_to_Vector3(qw, qx, qy, qz);
	return x, y, z;
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

		const int scale = 3;
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

		///각 꼭짓점 위치
		COORD a1 = ScreenCOORD(start, a);
		COORD b1 = ScreenCOORD(start, b);
		COORD c1 = ScreenCOORD(start, c);
		COORD d1 = ScreenCOORD(start, d);
		COORD e1 = ScreenCOORD(start, e);
		COORD f1 = ScreenCOORD(start, f);
		COORD g1 = ScreenCOORD(start, g);
		COORD h1 = ScreenCOORD(start, h);

		// 선출력
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

		// 면출력
		DrawSurface(a1, c1, b1, d1);


		// 중점출력
		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// 중심점 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// 중심점 2
		printf("mid point222");
		system("cls");	//출력한 문자 지우기

		//회전각 늘리기
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
		//printf("%f, %f, %f", X, Y, Z);	//나중에 지우기

		// 좌표위치확인
		gotoxy(a1.X, a1.Y);
		printf("a 위치");
		gotoxy(b1.X, b1.Y);
		printf("b 위치");
		gotoxy(c1.X, c1.Y);
		printf("c 위치");
		gotoxy(d1.X, d1.Y);
		printf("d 위치");
		gotoxy(e1.X, e1.Y);
		printf("e 위치");
		gotoxy(f1.X, f1.Y);
		printf("f 위치");
		gotoxy(g1.X, g1.Y);
		printf("g 위치");
		gotoxy(h1.X, h1.Y);
		printf("h 위치");

	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
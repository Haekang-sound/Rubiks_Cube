#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
// COORD는 좌표계 (왼쪽 위를 (0,0)잡는다. 특히 회전할때는 이 점을 중심으로 회전하니 주의)

// 벡터 구조체
struct Vector3
{
	float x, y, z;
};
//float X, Y, Z;	///각 회전축의 회전각
float x, y, z;	///회전연산 x,y,z값
float qw, qx, qy, qz;	///쿼터니언 벡터3개, 스칼라1개

int cubeX = 60, cubeY = 60, cubeZ = 60;

void gotoxy(short x, short y);		// 출력할 좌표에 커서를 옮겨주는 함수(xy평면)

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

///오일러 계산은 안써
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

///오일러 안쓰니까 안써도 돼
// float Euler_to_Quaternion(float x, float y, float z)	///오일러->쿼터니언 변환공식
// {
//	float cy = cos(x * M_PI / 180.0 * 0.5);
//	float sy = sin(x * M_PI / 180.0 * 0.5);
//	float cp = cos(y * M_PI / 180.0 * 0.5);
//	float sp = sin(y * M_PI / 180.0 * 0.5);
//	float cr = cos(z * M_PI / 180.0 * 0.5);
//	float sr = sin(z * M_PI / 180.0 * 0.5);
//	
//	qw = cy * cp * cr + sy * sp * sr;
//	qx = cy * cp * sr - sy * sp * cr;
//	qy = sy * cp * sr + cy * sp * cr;
//	qz = sy * cp * cr - cy * sp * sr;
// 	qw = ;
// 	qx = ;
// 	qy = ;
// 	qz = ;
// 	return qw, qx, qy, qz;
// }


///회전축 3개가 필요하다(사실 회전면이 3개다, 회전축으로 들어가있는건 평면의 법선벡터라는 입장이다)
///qx, qy, qz, qw도 3개가 필요하겠지

///오일러 안쓰니까 쿼터니언 변환 안해도 돼
// float Vector4_to_Vector3qx(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///쿼터니언 4차원 벡터->3차원 벡터 변환
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능
// 	return x, y, z;
// }
// float Vector4_to_Vector3(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///쿼터니언 4차원 벡터->3차원 벡터 변환
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능
// 	return x, y, z;
// }
// float Vector4_to_Vector3(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///쿼터니언 4차원 벡터->3차원 벡터 변환
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z값에 실수값을 더하거나 빼면 시점 거리 조절가능
// 	return x, y, z;
// }

 ///문제가 있는데... 회전 중심이 (0,0)이니... 이걸 바꿔야되겠지???
 /// 아니면 다 회전하고 (30,30)으로 이동하면 돼
/// 쿼터니언 회전식
 
///쿼터니언 회전각 xtheta, ytheta, ztheta 나중에 *90해라
float xtheta;
float ytheta;
float ztheta;	


//float xtheta, ytheta, ztheta;	///쿼터니언 회전각 xtheta, ytheta, ztheta
/// 쿼터니언 식 : 회전"만"을 표현한 것이다, 이걸로 점의 위치가 어떻게 옮겨지는지 계산해야돼
 /// 이거 회전행렬을 성분으로 나타낸거다. 계산한 결과는 따로 구해야돼
 
 ///회전행렬의 w,x, y, z 성분이다 이걸로 점의 회전 계산 따로 해야한다
 float rotateXvector(float xtheta)
 {
	float x11 = sqrt(1-(pow(cos(xtheta),2)))/ sin(xtheta);	//루트 어떻게 만들지?
	float y11 = 0/ sin(xtheta);
	float z11 = 0/ sin(xtheta);
	float w11 = cos(xtheta);
 	return x11, y11, z11, w11;
 }
 float rotateYvector(float ytheta)
 {
	 float x22 = 0/ sin(ytheta);
	 float y22 = sqrt(1 - (pow(cos(ytheta), 2))) / sin(ytheta);
	 float z22 = 0/ sin(ytheta);
	 float w22 = cos(ytheta);
	 return x22, y22, z22, w22;
 }
 float rotateZvector(float ztheta)
 {
	 float x33 = 0/ sin(ztheta);
	 float y33 = 0/ sin(ztheta);
	 float z33 = sqrt(1 - (pow(cos(ztheta), 2))) / sin(ztheta);
	 float w33 = cos(ztheta);
	 return x33, y33, z33, w33;
 }


 ///c언어로 만드는 회전행렬
///굳이 필요한가?

/// 회전 후에 점의 새로운 위치를 구해야 하는데.....회전행렬을 구해서 계산해야 할 듯한 느낌이 드는데....
/// 행렬 곱셈은 for문을 쓴다.....
/// 결과만 알고 있다면 행렬곱셈은 필요없다


/// 회전행렬 구해서 곱한 뒤 새로운 점 만들어야한다
 
 ///오일러 계산은 안써
 ///X회전
 float calculateX(int i, int j, int k)	/// x값
 {
	 //return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y값
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z값
 {
	// return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }

 ///Y회전
 float calculateX(int i, int j, int k)	/// x값
 {
	 //return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y값
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z값
 {
	// return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }

 ///Z회전
 float calculateX(int i, int j, int k)	/// x값
 {
	// return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y값
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z값
 {
	 //return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }


///--------------------------------------------------
 //x = (i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
// y = (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 //z = (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));


/////X회전 후 출력면 연산
//float calculateForSurfaceX(float cubeX, float cubeY, float cubeZ)
//{
//	
//
//	float x = sqrt(1 - (pow(cos(xtheta), 2))) / sin(xtheta);	//이건 회전한 점이 아니라, 회전행렬의 
//	float y = 0 / sin(xtheta);
//	
//	
//	float z = 0 / sin(xtheta);
//	
//	
//	float w = cos(xtheta);
//	return x, y, z, w;
//}


// float calculateForSurface(float cubeX, float cubeY, float cubeZ)	///회전 후 출력면 연산
// {
//  	x = (cubeX, cubeY, cubeZ) + 30;	///오일러회전 x,y,z 연산
//  	y = (cubeX, cubeY, cubeZ) + 30;
//  	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
//  	// 	Euler_to_Quaternion(x, y, z);	///오일러->쿼터니언 변환
//  	// 	Vector4_to_Vector3(qw, qx, qy, qz);
//  	return x, y, z;
// }

float calculateForSurfaceX(float cubeX, float cubeY, float cubeZ)	///X회전 후 출력면 연산
{
 	x = (cubeX, cubeY, cubeZ) + 30;	
 	y = (cubeX, cubeY, cubeZ) + 30;
 	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
 	
 	return x-30, y-30, z-30;
}
float calculateForSurfaceY(float cubeX, float cubeY, float cubeZ)	///Y회전 후 출력면 연산
{
 	x = (cubeX, cubeY, cubeZ) + 30;	
 	y = (cubeX, cubeY, cubeZ) + 30;
 	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
 
 	return x-30, y-30, z-30;
}
float calculateForSurfaceZ(float cubeX, float cubeY, float cubeZ)	///Z회전 후 출력면 연산
{
 	x = (cubeX, cubeY, cubeZ) + 30;	
 	y = (cubeX, cubeY, cubeZ) + 30;
 	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
 
 	return x-30, y-30, z-30;
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

	
		
		//		///현재 이미 원래 중심축을 기준으로 (현재 돌아가는 회전축) 정육면체가 형성이 됐는데
		/////회전축을 바꾸려면 이미 형성된 정육면체의 좌표를 기준으로 회전축을 재정의해서 회전공식을 새로 짠다?
		/////90*정수 회전이니까 회전축은 바뀌지 않음


		//// x축은 같고 y축은 거꾸로 그려져있음
		/////각 꼭짓점 좌표(3차원)
		/////x축 회전 후 8점 이동하는거 
		//Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceX(a2.x, a2.y, a2.z);
		//Vector3 a = { x,y,z };

		//Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceX(b2.x, b2.y, b2.z);
		//Vector3 b = { x,y,z };

		//Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceX(c2.x, c2.y, c2.z);
		//Vector3 c = { x,y,z };

		//Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceX(d2.x, d2.y, d2.z);
		//Vector3 d = { x,y,z };

		//Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceX(e2.x, e2.y, e2.z);
		//Vector3 e = { x,y,z };

		//Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceX(f2.x, f2.y, f2.z);
		//Vector3 f = { x,y,z };

		//Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceX(g2.x, g2.y, g2.z);
		//Vector3 g = { x,y,z };

		//Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceX(h2.x, h2.y, h2.z);
		//Vector3 h = { x,y,z };

		////--------------------------------------------
		/////y 회전 후 각 점 이동
		//Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceY(a2.x, a2.y, a2.z);
		//Vector3 a = { x,y,z };

		//Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceY(b2.x, b2.y, b2.z);
		//Vector3 b = { x,y,z };

		//Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceY(c2.x, c2.y, c2.z);
		//Vector3 c = { x,y,z };

		//Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceY(d2.x, d2.y, d2.z);
		//Vector3 d = { x,y,z };

		//Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceY(e2.x, e2.y, e2.z);
		//Vector3 e = { x,y,z };

		//Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		//calculateForSurfaceY(f2.x, f2.y, f2.z);
		//Vector3 f = { x,y,z };

		//Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceY(g2.x, g2.y, g2.z);
		//Vector3 g = { x,y,z };

		//Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		//calculateForSurfaceY(h2.x, h2.y, h2.z);
		//Vector3 h = { x,y,z };



		/////---------------------------------------------------------------------------------------------------------------



			///현재 이미 원래 중심축을 기준으로 (현재 돌아가는 회전축) 정육면체가 형성이 됐는데
		///회전축을 바꾸려면 이미 형성된 정육면체의 좌표를 기준으로 회전축을 재정의해서 회전공식을 새로 짠다?
		///90*정수 회전이니까 회전축은 바뀌지 않음



		///최악의 경우, 원점 회전을 바꿀 수 없다면
		///원점 중심으로 회전하고, (30,30) 평행이동을 한 뒤에 표시해야 할 수 있다
		/// 그리고 다음 회전할때는 다시 (-30,-30)하고 
		/// 회전 후에 
		/// 다시 (30,30) 평행이동한다

			///현재 이미 원래 중심축을 기준으로 (현재 돌아가는 회전축) 정육면체가 형성이 됐는데
		///회전축을 바꾸려면 이미 형성된 정육면체의 좌표를 기준으로 회전축을 재정의해서 회전공식을 새로 짠다?
		///90*정수 회전이니까 회전축은 바뀌지 않음


		// x축은 같고 y축은 거꾸로 그려져있음
		///각 꼭짓점 좌표(3차원)
		///x축 회전 후 8점 이동하는거 
		Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceX(a2.x, a2.y, a2.z);
		Vector3 a = { x,y,z };

		Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceX(b2.x, b2.y, b2.z);
		Vector3 b = { x,y,z };

		Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceX(c2.x, c2.y, c2.z);
		Vector3 c = { x,y,z };

		Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceX(d2.x, d2.y, d2.z);
		Vector3 d = { x,y,z };

		Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceX(e2.x, e2.y, e2.z);
		Vector3 e = { x,y,z };

		Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceX(f2.x, f2.y, f2.z);
		Vector3 f = { x,y,z };

		Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceX(g2.x, g2.y, g2.z);
		Vector3 g = { x,y,z };

		Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceX(h2.x, h2.y, h2.z);
		Vector3 h = { x,y,z };

		//--------------------------------------------
		///y 회전 후 각 점 이동
		Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceY(a2.x, a2.y, a2.z);
		Vector3 a = { x,y,z };

		Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceY(b2.x, b2.y, b2.z);
		Vector3 b = { x,y,z };

		Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceY(c2.x, c2.y, c2.z);
		Vector3 c = { x,y,z };

		Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceY(d2.x, d2.y, d2.z);
		Vector3 d = { x,y,z };

		Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceY(e2.x, e2.y, e2.z);
		Vector3 e = { x,y,z };

		Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceY(f2.x, f2.y, f2.z);
		Vector3 f = { x,y,z };

		Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceY(g2.x, g2.y, g2.z);
		Vector3 g = { x,y,z };

		Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceY(h2.x, h2.y, h2.z);
		Vector3 h = { x,y,z };



		///---------------------------------------------------------------------------------------------------------------



		//-----------------------------------------------

		///z 회전 후 각 점 이동
		Vector3 a2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceZ(a2.x, a2.y, a2.z);
		Vector3 a = { x,y,z };

		Vector3 b2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceZ(b2.x, b2.y, b2.z);
		Vector3 b = { x,y,z };

		Vector3 c2 = { centerX + (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceZ(c2.x, c2.y, c2.z);
		Vector3 c = { x,y,z };

		Vector3 d2 = { centerX - (cubeLength * scale) - 30  , centerY + (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceZ(d2.x, d2.y, d2.z);
		Vector3 d = { x,y,z };

		Vector3 e2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceZ(e2.x, e2.y, e2.z);
		Vector3 e = { x,y,z };

		Vector3 f2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ - (cubeLength * scale) - 30 };
		calculateForSurfaceZ(f2.x, f2.y, f2.z);
		Vector3 f = { x,y,z };

		Vector3 g2 = { centerX + (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceZ(g2.x, g2.y, g2.z);
		Vector3 g = { x,y,z };

		Vector3 h2 = { centerX - (cubeLength * scale) - 30  , centerY - (cubeLength * scale) - 30, centerZ + (cubeLength * scale) - 30 };
		calculateForSurfaceZ(h2.x, h2.y, h2.z);
		Vector3 h = { x,y,z };




		///-------------------------------------------------------------------------------------------------



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


		///회전의 중심은 한개// 축은 3개// 반지름이 바뀐다.. 아 반지름은 상관없구나, 축의방향과 theta만 중요하니까
		//MZ회전 반지름 
		//KA회전 반지름 =ED회전 중심=HY회전 중심	
		//OQ회전 반지름
		//WS회전 반지름
		//RF회전 반지름
		//GT회전 반지름
		//JU회전 반지름
		


		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// 중심점 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// 중심점 2
		printf("mid point222");
		system("cls");	//출력한 문자 지우기



		///회전각 늘리기(입력한 수의 *90만큼 돌아간다)
		if (GetAsyncKeyState('W')) { xtheta += 0.08; }
		if (GetAsyncKeyState('S')) { xtheta -= 0.08; }
		if (GetAsyncKeyState('A')) { ytheta -= 0.08; }
		if (GetAsyncKeyState('D')) { ytheta += 0.08; }
		if (GetAsyncKeyState('Q')) { ztheta += 0.08; }
		if (GetAsyncKeyState('E')) { ztheta -= 0.08; }

	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
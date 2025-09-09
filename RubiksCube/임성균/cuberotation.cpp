#include<stdio.h>
#include<Windows.h>
#include<math.h>
#define M_PI       3.14159265358979323846   // pi
// COORD�� ��ǥ�� (���� ���� (0,0)��´�. Ư�� ȸ���Ҷ��� �� ���� �߽����� ȸ���ϴ� ����)

// ���� ����ü
struct Vector3
{
	float x, y, z;
};
//float X, Y, Z;	///�� ȸ������ ȸ����
float x, y, z;	///ȸ������ x,y,z��
float qw, qx, qy, qz;	///���ʹϾ� ����3��, ��Į��1��

int cubeX = 60, cubeY = 60, cubeZ = 60;

void gotoxy(short x, short y);		// ����� ��ǥ�� Ŀ���� �Ű��ִ� �Լ�(xy���)

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

///���Ϸ� ����� �Ƚ�
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

///���Ϸ� �Ⱦ��ϱ� �Ƚᵵ ��
// float Euler_to_Quaternion(float x, float y, float z)	///���Ϸ�->���ʹϾ� ��ȯ����
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


///ȸ���� 3���� �ʿ��ϴ�(��� ȸ������ 3����, ȸ�������� ���ִ°� ����� �������Ͷ�� �����̴�)
///qx, qy, qz, qw�� 3���� �ʿ��ϰ���

///���Ϸ� �Ⱦ��ϱ� ���ʹϾ� ��ȯ ���ص� ��
// float Vector4_to_Vector3qx(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4���� ����->3���� ���� ��ȯ
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������
// 	return x, y, z;
// }
// float Vector4_to_Vector3(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4���� ����->3���� ���� ��ȯ
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������
// 	return x, y, z;
// }
// float Vector4_to_Vector3(float qw, float qx, float qy, float qz)
// {
// 	float x = 2 * (qx * qz - qw * qy);	///���ʹϾ� 4���� ����->3���� ���� ��ȯ
// 	float y = 2 * (qw * qx - qy * qz);
// 	float z = 2 * (qw * qw - qx * qx - qy * qy + qz * qz);	///z���� �Ǽ����� ���ϰų� ���� ���� �Ÿ� ��������
// 	return x, y, z;
// }

 ///������ �ִµ�... ȸ�� �߽��� (0,0)�̴�... �̰� �ٲ�ߵǰ���???
 /// �ƴϸ� �� ȸ���ϰ� (30,30)���� �̵��ϸ� ��
/// ���ʹϾ� ȸ����
 
///���ʹϾ� ȸ���� xtheta, ytheta, ztheta ���߿� *90�ض�
float xtheta;
float ytheta;
float ztheta;	


//float xtheta, ytheta, ztheta;	///���ʹϾ� ȸ���� xtheta, ytheta, ztheta
/// ���ʹϾ� �� : ȸ��"��"�� ǥ���� ���̴�, �̰ɷ� ���� ��ġ�� ��� �Ű������� ����ؾߵ�
 /// �̰� ȸ������� �������� ��Ÿ���Ŵ�. ����� ����� ���� ���ؾߵ�
 
 ///ȸ������� w,x, y, z �����̴� �̰ɷ� ���� ȸ�� ��� ���� �ؾ��Ѵ�
 float rotateXvector(float xtheta)
 {
	float x11 = sqrt(1-(pow(cos(xtheta),2)))/ sin(xtheta);	//��Ʈ ��� ������?
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


 ///c���� ����� ȸ�����
///���� �ʿ��Ѱ�?

/// ȸ�� �Ŀ� ���� ���ο� ��ġ�� ���ؾ� �ϴµ�.....ȸ������� ���ؼ� ����ؾ� �� ���� ������ ��µ�....
/// ��� ������ for���� ����.....
/// ����� �˰� �ִٸ� ��İ����� �ʿ����


/// ȸ����� ���ؼ� ���� �� ���ο� �� �������Ѵ�
 
 ///���Ϸ� ����� �Ƚ�
 ///Xȸ��
 float calculateX(int i, int j, int k)	/// x��
 {
	 //return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y��
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z��
 {
	// return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }

 ///Yȸ��
 float calculateX(int i, int j, int k)	/// x��
 {
	 //return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y��
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z��
 {
	// return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }

 ///Zȸ��
 float calculateX(int i, int j, int k)	/// x��
 {
	// return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
	 return	(i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
 }
 float calculateY(int i, int j, int k)	/// y��
 {
	// return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
	 return (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 }
 float calculateZ(int i, int j, int k)	/// z��
 {
	 //return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
	 return (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));
 }


///--------------------------------------------------
 //x = (i * (1 - 2 * cubeY * cubeY - 2 * cubeZ * cubeZ) + j * (2 * cubeX * cubeY - 2 * cubeZ * 1) + k * (2 * cubeX * cubeZ + 2 * cubeY * 1));
// y = (i * (2 * cubeX * cubeY + 2 * cubeZ * 1) + j * (1 - 2 * cubeX * cubeX - 2 * cubeZ * cubeZ) + k * (2 * cubeY * cubeZ - 2 * cubeX * 1));
 //z = (i * (2 * cubeX * cubeZ - 2 * cubeY * 1) + j * (2 * cubeY * cubeZ + 2 * cubeX * 1) + k * (1 - 2 * cubeX * cubeX - 2 * cubeY * cubeY));


/////Xȸ�� �� ��¸� ����
//float calculateForSurfaceX(float cubeX, float cubeY, float cubeZ)
//{
//	
//
//	float x = sqrt(1 - (pow(cos(xtheta), 2))) / sin(xtheta);	//�̰� ȸ���� ���� �ƴ϶�, ȸ������� 
//	float y = 0 / sin(xtheta);
//	
//	
//	float z = 0 / sin(xtheta);
//	
//	
//	float w = cos(xtheta);
//	return x, y, z, w;
//}


// float calculateForSurface(float cubeX, float cubeY, float cubeZ)	///ȸ�� �� ��¸� ����
// {
//  	x = (cubeX, cubeY, cubeZ) + 30;	///���Ϸ�ȸ�� x,y,z ����
//  	y = (cubeX, cubeY, cubeZ) + 30;
//  	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
//  	// 	Euler_to_Quaternion(x, y, z);	///���Ϸ�->���ʹϾ� ��ȯ
//  	// 	Vector4_to_Vector3(qw, qx, qy, qz);
//  	return x, y, z;
// }

float calculateForSurfaceX(float cubeX, float cubeY, float cubeZ)	///Xȸ�� �� ��¸� ����
{
 	x = (cubeX, cubeY, cubeZ) + 30;	
 	y = (cubeX, cubeY, cubeZ) + 30;
 	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
 	
 	return x-30, y-30, z-30;
}
float calculateForSurfaceY(float cubeX, float cubeY, float cubeZ)	///Yȸ�� �� ��¸� ����
{
 	x = (cubeX, cubeY, cubeZ) + 30;	
 	y = (cubeX, cubeY, cubeZ) + 30;
 	z = calculateZ(cubeX, cubeY, cubeZ) + 30;
 
 	return x-30, y-30, z-30;
}
float calculateForSurfaceZ(float cubeX, float cubeY, float cubeZ)	///Zȸ�� �� ��¸� ����
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

	
		
		//		///���� �̹� ���� �߽����� �������� (���� ���ư��� ȸ����) ������ü�� ������ �ƴµ�
		/////ȸ������ �ٲٷ��� �̹� ������ ������ü�� ��ǥ�� �������� ȸ������ �������ؼ� ȸ�������� ���� §��?
		/////90*���� ȸ���̴ϱ� ȸ������ �ٲ��� ����


		//// x���� ���� y���� �Ųٷ� �׷�������
		/////�� ������ ��ǥ(3����)
		/////x�� ȸ�� �� 8�� �̵��ϴ°� 
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
		/////y ȸ�� �� �� �� �̵�
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



			///���� �̹� ���� �߽����� �������� (���� ���ư��� ȸ����) ������ü�� ������ �ƴµ�
		///ȸ������ �ٲٷ��� �̹� ������ ������ü�� ��ǥ�� �������� ȸ������ �������ؼ� ȸ�������� ���� §��?
		///90*���� ȸ���̴ϱ� ȸ������ �ٲ��� ����



		///�־��� ���, ���� ȸ���� �ٲ� �� ���ٸ�
		///���� �߽����� ȸ���ϰ�, (30,30) �����̵��� �� �ڿ� ǥ���ؾ� �� �� �ִ�
		/// �׸��� ���� ȸ���Ҷ��� �ٽ� (-30,-30)�ϰ� 
		/// ȸ�� �Ŀ� 
		/// �ٽ� (30,30) �����̵��Ѵ�

			///���� �̹� ���� �߽����� �������� (���� ���ư��� ȸ����) ������ü�� ������ �ƴµ�
		///ȸ������ �ٲٷ��� �̹� ������ ������ü�� ��ǥ�� �������� ȸ������ �������ؼ� ȸ�������� ���� §��?
		///90*���� ȸ���̴ϱ� ȸ������ �ٲ��� ����


		// x���� ���� y���� �Ųٷ� �׷�������
		///�� ������ ��ǥ(3����)
		///x�� ȸ�� �� 8�� �̵��ϴ°� 
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
		///y ȸ�� �� �� �� �̵�
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

		///z ȸ�� �� �� �� �̵�
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


		///ȸ���� �߽��� �Ѱ�// ���� 3��// �������� �ٲ��.. �� �������� ���������, ���ǹ���� theta�� �߿��ϴϱ�
		//MZȸ�� ������ 
		//KAȸ�� ������ =EDȸ�� �߽�=HYȸ�� �߽�	
		//OQȸ�� ������
		//WSȸ�� ������
		//RFȸ�� ������
		//GTȸ�� ������
		//JUȸ�� ������
		


		gotoxy(middlePoint.X - strlen("mid point") / 2, middlePoint.Y);			// �߽��� 1
		printf("mid point");

		gotoxy(middlePoint2.X - strlen("mid point222") / 2, middlePoint2.Y);	// �߽��� 2
		printf("mid point222");
		system("cls");	//����� ���� �����



		///ȸ���� �ø���(�Է��� ���� *90��ŭ ���ư���)
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
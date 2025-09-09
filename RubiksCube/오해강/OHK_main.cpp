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

void gotoxy(short x, short y);								// ����� ��ǥ�� Ŀ���� �Ű��ִ� �Լ�
COORD ScreenCOORD(Vector3 startPoint, Vector3 endPoint);	//, Vector3 ����b
void DrawLine(COORD firstPoint, COORD secondPoint);			// ��ǥ�� �Է¹ް� ���� �ߴ� �Լ�

/// ���� �׸��� �Լ�
// ���� �׸��� �Լ��� ��������� ����� �ʰڴٰ� �����ߴµ�
// �����ϸ� �����Ҽ��� �׳� ������ �Լ��� �ƴѰ� ����.
//
void DrawSurface(COORD x1, COORD x2, COORD y1, COORD y2)
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
}

int main(void)
{
	system("mode con cols=120 lines=60");
	
	while (1)
	{
		// ���� ����� 
		int screenWidth = 60 ;
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
		const int cubeLength = 20;

		float centerX = screenWidth / 2;
		float centerY = screenHeight / 2;
		float centerZ = 30;

		// ť��
		
		Vector3 start = { centerX , centerY, -100 }; // ������ start point

		Vector3 center = { centerX , centerY, }; // �߾���ǥ
		Vector3 center2 = { centerX , centerY, centerZ }; // z�� �ٸ� �߾���ǥ

		COORD middlePoint = ScreenCOORD(start, center);
		COORD middlePoint2 = ScreenCOORD(start, center2);	// �ٸ� �߾���ǥ ��¿�

		// x���� ���� y���� �Ųٷ� �׷�������
		Vector3 a = { centerX - (cubeLength * scale), centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 b = { centerX + (cubeLength * scale), centerY + (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 c = { centerX + (cubeLength * scale), centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 d = { centerX - (cubeLength * scale), centerY + (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 e = { centerX - (cubeLength * scale), centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 f = { centerX + (cubeLength * scale), centerY - (cubeLength * scale), centerZ - (cubeLength * scale) };
		Vector3 g = { centerX + (cubeLength * scale), centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };
		Vector3 h = { centerX - (cubeLength * scale), centerY - (cubeLength * scale), centerZ + (cubeLength * scale) };

		COORD a1 = ScreenCOORD(start, a);
		COORD b1 = ScreenCOORD(start, b);
		COORD c1 = ScreenCOORD(start, c);
		COORD d1 = ScreenCOORD(start, d);

		COORD e1 = ScreenCOORD(start, e);
		COORD f1 = ScreenCOORD(start, f);
		COORD g1 = ScreenCOORD(start, g);
		COORD h1 = ScreenCOORD(start, h);

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

		
	}
	return 0;
}

void gotoxy(short x, short y) {
	COORD pos = { x*2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/// 2���� ��ǥ�� ã�� �Լ�
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
	// �� ���� ��ġ�� ���� ��� �� �ڸ��� ����� �Լ� ����
	if (firstPoint.X == secondPoint.X && firstPoint.Y == secondPoint.Y)	
	{
		gotoxy(firstPoint.X, firstPoint.Y);
		printf("*");
		return;
	}
	
	// �� ���� y�� ���� ��� x�� ����ϴ� �Լ��� ����
	else if (firstPoint.Y == secondPoint.Y)									
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
	
	// �� ���� x���� ���� ��� y�� ����ϴ� �Լ� ����
	else if (firstPoint.X == secondPoint.X)									
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
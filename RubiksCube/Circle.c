#include "Circle.h"

Intersection intersections[54]; // ���� 6 * 9 = 54 ��
int intersectionsIndex;

// Circle ���� COORD �迭�� �޾Ƽ� �׸��� ����
void GetCirclePoint(Circle circle[], COORD(*circlePoint)[180])
{
	double x = 0;
	double y = 0;

	double radian;
	for (int circleIndex = 0; circleIndex < 9; circleIndex++)
	{
		for (int degree = 0; degree < 180; degree++)
		{
			radian = GetRadian(degree * 2);

			x = circle[circleIndex].r * cos(radian);
			y = circle[circleIndex].r * sin(radian);

			COORD tempPoint = { (short)(circle[circleIndex].center.X + x), (short)(circle[circleIndex].center.Y + y) };
			circlePoint[circleIndex][degree] = tempPoint;
		}
	}
}

//�Ź� ���� ��ġ�� �������� ���� �迭�� ������ �� ������ ���ٰ� �׸���
void MakeCurcle(Circle* circles, COORD(*circlePoint)[180])
{
	// ��� ���� �߽�
	COORD circleCenter = { 50, 50 };

	// �߽� 3�� �и�
	int xDistance = 12;
	int yDistance = 19;

	COORD circlesTopCenter = { circleCenter.X , circleCenter.Y - yDistance };
	COORD circlesLeftCenter = { circleCenter.X - xDistance, circleCenter.Y };
	COORD circlesRightCenter = { circleCenter.X + xDistance , circleCenter.Y };

	// �� ������ ����
	double defaultCircleScale = 6.0f;

	const double scale1 = 2.8f * defaultCircleScale;
	const double scale2 = 3.4f * defaultCircleScale;
	const double scale3 = 4.0f * defaultCircleScale;

	// �ð� �� �� �ʱ�ȭ �ϴ� �� ���� ������ �ִٸ� �����丵 �ϱ� -> �迭�� ����?
	Circle circleTop1 = { {circlesTopCenter.X, circlesTopCenter.Y}, (int)scale1, 0 };
	Circle circleTop2 = { {circlesTopCenter.X, circlesTopCenter.Y}, (int)scale2, 0 };
	Circle circleTop3 = { {circlesTopCenter.X, circlesTopCenter.Y}, (int)scale3, 0 };
	circles[0] = circleTop1;
	circles[1] = circleTop2;
	circles[2] = circleTop3;

	Circle circleLeft1 = { {circlesLeftCenter.X, circlesLeftCenter.Y}, (int)scale1, 0 };
	Circle circleLeft2 = { {circlesLeftCenter.X, circlesLeftCenter.Y}, (int)scale2, 0 };
	Circle circleLeft3 = { {circlesLeftCenter.X, circlesLeftCenter.Y}, (int)scale3, 0 };
	circles[3] = circleLeft1;
	circles[4] = circleLeft2;
	circles[5] = circleLeft3;

	Circle circleRight1 = { {circlesRightCenter.X, circlesRightCenter.Y}, (int)scale1, 0 };
	Circle circleRight2 = { {circlesRightCenter.X, circlesRightCenter.Y}, (int)scale2, 0 };
	Circle circleRight3 = { {circlesRightCenter.X, circlesRightCenter.Y}, (int)scale3, 0 };
	circles[6] = circleRight1;
	circles[7] = circleRight2;
	circles[8] = circleRight3;

	GetCirclePoint(circles, circlePoint);
}

void SetCirclePoint(Circle* circle, int intersectionIndex)
{
	double radian = GetRadian(circle->intersections[intersectionIndex]->theta);

	double x = circle->r * cos(radian);
	double y = circle->r * sin(radian);

	circle->intersections[intersectionIndex]->intersection.X = (short)(circle->center.X + x);
	circle->intersections[intersectionIndex]->intersection.Y = (short)(circle->center.Y + y);
}

void DrawCircle(COORD(*circlePoint)[180])
{
	SetColor(15);
	for (int circleIndex = 0; circleIndex < 9; circleIndex++)
	{
		for (int degree = 0; degree < 180; degree++)
		{
			ScreenPrint(circlePoint[circleIndex][degree].X, circlePoint[circleIndex][degree].Y, "��");
		}
	}
}

void FindIntersection(Circle c1, Circle c2, COORD* intersection) 
{
	double distance = sqrt(pow(c1.center.X - c2.center.X, 2) + pow(c1.center.Y - c2.center.Y, 2));

	// common Chord = �� ���� ���� ��
	// circle 1 �߽� ���� �������� �߽� ���� �Ÿ� (��Ÿ��� ����)
	double commonChordCenter = (pow(c1.r, 2) - pow(c2.r, 2) + pow(distance, 2)) / (2 * distance);
	// ������ 2���� 1 ���� (��Ÿ��� ����)
	double commonChordH = sqrt(pow(c1.r, 2) - pow(commonChordCenter, 2));

	// ������ �߽� ��ǥ
	double x2 = c1.center.X + commonChordCenter * (c2.center.X - c1.center.X) / distance;
	double y2 = c1.center.Y + commonChordCenter * (c2.center.Y - c1.center.Y) / distance;

	// ��ʽ� ��� 
	COORD intersection1 = { (short)(x2 + commonChordH * (c2.center.Y - c1.center.Y) / distance), 
		(short)(y2 - commonChordH * (c2.center.X - c1.center.X) / distance) };
	COORD intersection2 = { (short)(x2 - commonChordH * (c2.center.Y - c1.center.Y) / distance), 
		(short)(y2 + commonChordH * (c2.center.X - c1.center.X) / distance) };

	intersection[0] = intersection1;
	intersection[1] = intersection2;
}

void SetIntersection(Cube* cube, Circle* circles)
{
	// ���� �ӽ÷� ���� �ڵ�
	// �ڷᱸ���� ���ļ� �����ؾ���
	COORD intersections[2];
	COORD* intersectionPtr = intersections;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 3; j < 6; j++)
		{
			FindIntersection(circles[i], circles[j], intersectionPtr);

			AddIntersection(&circles[i], &circles[j], intersectionPtr[0], &cube->cubeArr[1][i][(j - 3)].color); // purple
			AddIntersection(&circles[i], &circles[j], intersectionPtr[1], &cube->cubeArr[3][i][(2 - (j - 3))].color); //red
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 6; j < 9; j++)
		{
			FindIntersection(circles[i], circles[j], intersectionPtr);

			AddIntersection(&circles[i], &circles[j], intersectionPtr[0], &cube->cubeArr[2][i][(j - 6)].color); // green
			AddIntersection(&circles[i], &circles[j], intersectionPtr[1], &cube->cubeArr[0][i][2 - (j - 6)].color); // blue
		}
	}

	for (int i = 3; i < 6; i++)
	{
		for (int j = 6; j < 9; j++)
		{
			FindIntersection(circles[i], circles[j], intersectionPtr);

			AddIntersection(&circles[i], &circles[j], intersectionPtr[0], &cube->cubeArr[4][2 - (i - 3)][2 - (j - 6)].color); // yellow
			AddIntersection(&circles[i], &circles[j], intersectionPtr[1], &cube->cubeArr[5][(i - 3)][2 - (j - 6)].color); // cyan
		}
	}
}

void PrintIntersection(COORD intersection, int* color)
{
	SetColor(*color);
	ScreenPrint(intersection.X, intersection.Y, "��");
	ScreenPrint(intersection.X + 1, intersection.Y, "��");
	ScreenPrint(intersection.X - 1, intersection.Y, "��");

	ScreenPrint(intersection.X, intersection.Y + 1, "��");
	ScreenPrint(intersection.X + 1, intersection.Y + 1, "��");
	ScreenPrint(intersection.X - 1, intersection.Y + 1, "��");

	ScreenPrint(intersection.X, intersection.Y - 1, "��");
	ScreenPrint(intersection.X + 1, intersection.Y - 1, "��");
	ScreenPrint(intersection.X - 1, intersection.Y - 1, "��");
}

void PrintCircleIntersection(Circle circle)
{
	for (int i = 0; i < 12; i++)
	{
		PrintIntersection(circle.intersections[i]->intersection, circle.intersections[i]->color);
	}
}

void AddIntersection(Circle* circle1, Circle* circle2, COORD intersection, int* color)
{
	Intersection newIntersection = { intersection, color };
	intersections[intersectionsIndex++] = newIntersection;
	(*circle1).intersections[(*circle1).intersectionIndex++] = &intersections[intersectionsIndex - 1];
	(*circle2).intersections[(*circle2).intersectionIndex++] = &intersections[intersectionsIndex - 1];
}

void SetInsectionAngle(Circle* circle)
{
	// ���� ��� // ũ�� // dot product �ʿ�
	double dotProduct;

	double uLength;
	double vLength;

	double cosTheta;
	double theta;

	for (int i = 0; i < 12; i++)
	{
		uLength = sqrt(pow(circle->r, 2));
		vLength = sqrt(pow((circle->intersections[i]->intersection.X - circle->center.X), 2) +
			pow((circle->intersections[i]->intersection.Y - circle->center.Y), 2));

// 		vLength = sqrt(circle.intersections[i].intersection.X ^ 2 - circle.center.X
// 			+ circle.intersections[i].intersection.Y ^ 2 - circle.center.Y);

		dotProduct = (circle->intersections[i]->intersection.X - circle->center.X)* circle->r
			+ (circle->intersections[i]->intersection.Y - circle->center.Y);

		cosTheta = dotProduct / (uLength * vLength); // ũ��: �� -> �и�

		//�ε� �Ǽ��� ������ ���� ������ cos ���� ������ ���� �� ���� ������ �ٽ� �־��ֱ�
		if (cosTheta < -1) cosTheta = -1;
		else if (cosTheta > 1) cosTheta = 1;

		theta = acos(cosTheta);

		// �ڻ����� cos x == cos (180 - x + 180) �̶�� ������ ������ ����
		// ���� �߽ɺ��� ���� ������ theta < 180 �̰�
		// �Ʒ� ������ theta > 180 �̴ϱ� ���� �������ֱ�

		//��
		if (circle->intersections[i]->intersection.Y < circle->center.Y)
		{
			circle->intersections[i]->theta = GetDegree(theta);
		}
		//�Ʒ�
		else
		{
			circle->intersections[i]->theta = 180 - GetDegree(theta) + 180;
		}
	}
}
#include "Circle.h"

Intersection intersections[54]; // 교점 6 * 9 = 54 개
int intersectionsIndex;

// Circle 말고 COORD 배열을 받아서 그리게 변경
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

//매번 점의 위치를 연산하지 말고 배열에 연산한 값 저장해 놨다가 그리기
void MakeCurcle(Circle* circles, COORD(*circlePoint)[180])
{
	// 모든 원의 중심
	COORD circleCenter = { 50, 50 };

	// 중심 3개 분리
	int xDistance = 12;
	int yDistance = 19;

	COORD circlesTopCenter = { circleCenter.X , circleCenter.Y - yDistance };
	COORD circlesLeftCenter = { circleCenter.X - xDistance, circleCenter.Y };
	COORD circlesRightCenter = { circleCenter.X + xDistance , circleCenter.Y };

	// 원 반지름 설정
	double defaultCircleScale = 6.0f;

	const double scale1 = 2.8f * defaultCircleScale;
	const double scale2 = 3.4f * defaultCircleScale;
	const double scale3 = 4.0f * defaultCircleScale;

	// 시간 날 때 초기화 하는 더 좋은 구조가 있다면 리팩토링 하기 -> 배열로 변경?
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
			ScreenPrint(circlePoint[circleIndex][degree].X, circlePoint[circleIndex][degree].Y, "■");
		}
	}
}

void FindIntersection(Circle c1, Circle c2, COORD* intersection) 
{
	double distance = sqrt(pow(c1.center.X - c2.center.X, 2) + pow(c1.center.Y - c2.center.Y, 2));

	// common Chord = 두 원의 공통 현
	// circle 1 중심 부터 공통현의 중심 까지 거리 (피타고라스 정리)
	double commonChordCenter = (pow(c1.r, 2) - pow(c2.r, 2) + pow(distance, 2)) / (2 * distance);
	// 공통현 2분의 1 길이 (피타고라스 정리)
	double commonChordH = sqrt(pow(c1.r, 2) - pow(commonChordCenter, 2));

	// 공통현 중심 좌표
	double x2 = c1.center.X + commonChordCenter * (c2.center.X - c1.center.X) / distance;
	double y2 = c1.center.Y + commonChordCenter * (c2.center.Y - c1.center.Y) / distance;

	// 비례식 사용 
	COORD intersection1 = { (short)(x2 + commonChordH * (c2.center.Y - c1.center.Y) / distance), 
		(short)(y2 - commonChordH * (c2.center.X - c1.center.X) / distance) };
	COORD intersection2 = { (short)(x2 - commonChordH * (c2.center.Y - c1.center.Y) / distance), 
		(short)(y2 + commonChordH * (c2.center.X - c1.center.X) / distance) };

	intersection[0] = intersection1;
	intersection[1] = intersection2;
}

void SetIntersection(Cube* cube, Circle* circles)
{
	// 전부 임시로 만든 코드
	// 자료구조와 합쳐서 수정해야함
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
	ScreenPrint(intersection.X, intersection.Y, "■");
	ScreenPrint(intersection.X + 1, intersection.Y, "■");
	ScreenPrint(intersection.X - 1, intersection.Y, "■");

	ScreenPrint(intersection.X, intersection.Y + 1, "■");
	ScreenPrint(intersection.X + 1, intersection.Y + 1, "■");
	ScreenPrint(intersection.X - 1, intersection.Y + 1, "■");

	ScreenPrint(intersection.X, intersection.Y - 1, "■");
	ScreenPrint(intersection.X + 1, intersection.Y - 1, "■");
	ScreenPrint(intersection.X - 1, intersection.Y - 1, "■");
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
	// 내적 사용 // 크기 // dot product 필요
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

		cosTheta = dotProduct / (uLength * vLength); // 크기: 곱 -> 분모

		//부동 실수점 연산의 오류 때문에 cos 범위 밖으로 나갈 때 범위 안으로 다시 넣어주기
		if (cosTheta < -1) cosTheta = -1;
		else if (cosTheta > 1) cosTheta = 1;

		theta = acos(cosTheta);

		// 코사인은 cos x == cos (180 - x + 180) 이라는 성질을 가지고 있음
		// 원의 중심보다 위에 있으면 theta < 180 이고
		// 아래 있으면 theta > 180 이니까 직접 보정해주기

		//위
		if (circle->intersections[i]->intersection.Y < circle->center.Y)
		{
			circle->intersections[i]->theta = GetDegree(theta);
		}
		//아래
		else
		{
			circle->intersections[i]->theta = 180 - GetDegree(theta) + 180;
		}
	}
}
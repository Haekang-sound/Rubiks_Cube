#include "Mathematics.h"
#define PI 3.1415926535

// 각도를 입력하면 라디안을 반환하는 함수
double GetRadian(int num)
{
	return num * (PI / 180);
}

// 라디안을 입력하면 각도를 반환하는 함수
int GetDegree(double num)
{
	return num * (180 / PI);
}
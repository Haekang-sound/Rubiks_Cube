#include "Mathematics.h"
#define PI 3.1415926535

// ������ �Է��ϸ� ������ ��ȯ�ϴ� �Լ�
double GetRadian(int num)
{
	return num * (PI / 180);
}

// ������ �Է��ϸ� ������ ��ȯ�ϴ� �Լ�
int GetDegree(double num)
{
	return num * (180 / PI);
}
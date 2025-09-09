#include<math.h>



double calculateX(int i, int j, int k, double X, double Y, double Z)	///오일러회전 x값
{
	return j * sin(X) * sin(Y) * cos(Z)
		- k * cos(X) * sin(Y) * cos(Z)
		+ j * cos(X) * sin(Z)
		+ k * sin(X) * sin(Z)
		+ i * cos(Y) * cos(Z) + 30;
}
double calculateY(int i, int j, int k, double X, double Y, double Z)	///오일러회전 y값
{
	return j * cos(X) * cos(Z)
		+ k * sin(X) * cos(Z)
		- j * sin(X) * sin(Y) * sin(Z)
		+ k * cos(X) * sin(Y) * sin(Z)
		- i * cos(Y) * sin(Z) + 30;
}
double calculateZ(int i, int j, int k, double X, double Y, double Z)	///오일러회전 z값
{
	return k * cos(X) * cos(Y)
		- j * sin(X) * cos(Y)
		+ i * sin(Y) + 15;
}

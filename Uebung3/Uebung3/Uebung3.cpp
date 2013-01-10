// Uebung3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Templates.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	int k = 5;
	double l = 3.14;

	double a_data[] = { 2, 3, 5, 9 };
	double b_data[] = { 1, 0, 0, 1 };
	double c_data[] = { 3, 0, 2, 5 };
	double d_data[4];
	Array<double> A(a_data,4);
	Array<double> B(b_data,4);
	Array<double> C(c_data,4);
	Array<double> D(d_data,4);
	D = A + (B + C) + C + (A + B);
	D.print();
	D = A - (C - B) - C - (A - B);
	D.print();

	D = k*A + B + C*l;
	D.print();

	double x = A**B;
	cout << x  << endl;

}


// Uebung4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomAccessFile.hpp"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	char a = 't';
	RandomAccessFile* rf = new RandomAccessFile("tst.bin");
	rf->write(a);
	RandomAccessFile* rf2 = new RandomAccessFile("tst.bin");
	cout << rf2->read<char>(0) << endl;
}


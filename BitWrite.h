#pragma once
#include<iostream>
using namespace std;
#include<fstream>

class BitWrite
{
	char buf;
	int Tbits;
	ostream& out;
public:

	BitWrite(ostream & os) : out(os), buf(0), Tbits(0)
	{
		// xóa bộ đệm và bộ đếm bit
	}

	void flush();   	 // ghi bộ đệm vào tập tin đầu ra và xóa nó
	void writeBit(int i); // Viết bit có ý nghĩa ít nhất của đối số vào bộ đệm bit
};


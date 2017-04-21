#pragma once
#include "Definition.h"
#include <iostream>

class CLongNumber
{
public:
	CLongNumber();
	CLongNumber(const std::vector<int>& numberVec);
	CLongNumber(const std::string & numberStr);
	~CLongNumber();
	
	void setDenialSign(bool minus);
	bool getSign() const;

	int getValue(int i) const;

	size_t getSize() const;		 

	void printNumber() const;

	std::vector<int> getNumber() const;

	void operator =(const CLongNumber a);
private:
	std::vector<int> m_number;
	bool denialSign = false;

private:
	void deleteZero();
}; 

bool const operator >(const CLongNumber & a, const CLongNumber & b);
bool const operator >=(const CLongNumber & a, const CLongNumber & b);
bool const operator <(const CLongNumber & a, const CLongNumber & b);
bool const operator <=(const CLongNumber & a, const CLongNumber & b);
bool const operator ==(const CLongNumber & a, const CLongNumber & b);

CLongNumber const operator *(const CLongNumber & a, const CLongNumber & b);
CLongNumber const operator +(const CLongNumber & a, const CLongNumber & b);
CLongNumber const operator -(const CLongNumber & a, const CLongNumber & b);
CLongNumber const operator /(const CLongNumber & a, const CLongNumber & b);

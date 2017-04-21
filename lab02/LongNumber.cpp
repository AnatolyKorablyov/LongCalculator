#include "LongNumber.h"
#include <algorithm> 


CLongNumber::CLongNumber()
{
}

CLongNumber::CLongNumber(const std::vector<int> & numberVec)
{
	for (auto it : numberVec)
	{
		m_number.push_back(it);
	}
	if (m_number.size() != 1)
	{
		deleteZero();
	}
}

CLongNumber::CLongNumber(const std::string & numberStr)
{
	if (numberStr[0] == '-')
	{
		denialSign = true;
	}
	else
	{
		m_number.push_back(int(numberStr[0]) - int('0'));
	}


	for (size_t i = 1; i < numberStr.length(); ++i)
	{
		m_number.push_back(int(numberStr[i]) - int('0'));
	}
	if (m_number.size() != 1)
	{
		deleteZero();
	}
}

CLongNumber::~CLongNumber()
{
}

void CLongNumber::setDenialSign(bool minus)
{
	denialSign = minus;
}

bool CLongNumber::getSign() const
{
	return denialSign;
}


int CLongNumber::getValue(int i) const
{
	return m_number[i];
}

size_t CLongNumber::getSize() const
{
	return m_number.size();
}

void CLongNumber::printNumber()	const
{
	if (denialSign)
	{
		std::cout << "-";
	}
	for (auto it : m_number)
	{
		std::cout << it;
	}
	std::cout << std::endl;
}

std::vector<int> CLongNumber::getNumber() const
{
	return m_number;
}

void CLongNumber::operator=(const CLongNumber a)
{
	denialSign = a.getSign();
	m_number.clear();		
	for (int i = 0; i < a.getSize(); i++)
	{
		m_number.push_back(a.getValue(i));
	}
}

void CLongNumber::deleteZero()
{
	bool zer = true;
	for (int i = 0; i < m_number.size(); i++)
	{
		if (zer && (m_number[i] == 0))
		{
			m_number.erase(m_number.begin());
			i--;
		}
		else
		{
			zer = false;
		}
	}
}

bool const operator>(const CLongNumber & a, const CLongNumber & b)
{
	if (a.getSize() > b.getSize())
	{
		return true;
	}
	else if (a.getSize() < b.getSize())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < a.getSize(); i++)
		{
			if (a.getValue(i) > b.getValue(i))
			{
				return true;
			}
			else if (a.getValue(i) < b.getValue(i))
			{
				return false;
			}
		}
	}
	return false;
}

bool const operator>=(const CLongNumber & a, const CLongNumber & b)
{
	if (a.getSize() > b.getSize())
	{
		return true;
	}
	else if (a.getSize() < b.getSize())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < a.getSize(); i++)
		{
			if (a.getValue(i) > b.getValue(i))
			{
				return true;
			}
			else if (a.getValue(i) < b.getValue(i))
			{
				return false;
			}
		}
	}
	return true;
}

bool const operator<(const CLongNumber & a, const CLongNumber & b)
{
	return (!(a >= b));
}

bool const operator<=(const CLongNumber & a, const CLongNumber & b)
{
	return ((a < b) || (!(a > b) && !(a < b)));
}

bool const operator==(const CLongNumber & a, const CLongNumber & b)
{
	return (!(a > b) && !(a < b));
}

CLongNumber const operator*(const CLongNumber & a, const CLongNumber & b)
{
	std::vector<int> vecNum;
	vecNum.push_back(0);
	CLongNumber result(vecNum);

	int countB = b.getSize() - 1;
	int countA = a.getSize() - 1;

	int number = 0;
	int addNumber = 0;
	std::vector<int> longNum;
	for (int i = countA; i >= 0; i--)
	{
		bool large = false;
		longNum.clear();
		for (int j = countB; j >= 0; j--)
		{
			number = number / 10 + a.getValue(i) * b.getValue(j);
			large = false;
			if (number > 9)
			{
				large = true;
			}
			longNum.insert(longNum.begin(), number % 10);
		}
		if (large)
		{
			longNum.insert(longNum.begin(), number / 10);
		}

		
		
		for (int numZero = 0; numZero < countA - i; numZero++)
		{
			longNum.push_back(0);
		}

		CLongNumber addLongNum(longNum);

		result = result + addLongNum;

		number = 0;
	}

	return result;
}

CLongNumber const operator+(const CLongNumber & a, const CLongNumber & b)
{
	std::vector<int> result;
	int countB = b.getSize() - 1;
	int countA = a.getSize() - 1;

	int number = 0;
	int addNumber = 0;
	for (int i = std::max(countA, countB); i >= 0; i--)
	{
		if (countA >= 0 && countB >= 0)
		{
			number = addNumber + a.getValue(countA) + b.getValue(countB);
		}
		else if (countB >= 0)
		{
			number = addNumber + b.getValue(countB);
		}
		else if (countA >= 0)
		{
			number = addNumber + a.getValue(countA);
		}
		--countA;
		--countB;

		addNumber = number / 10;
		number = number % 10;

		result.insert(result.begin(), number);
		number = 0;
	}

	if (addNumber != 0)
	{
		result.insert(result.begin(), addNumber);
	}
	CLongNumber res(result);
	return res;
}

CLongNumber const operator-(const CLongNumber & a, const CLongNumber & b)
{
	CLongNumber fNum = a;
	CLongNumber sNum = b;

	if (b > a)
	{
		fNum = b;
		sNum = a;
	}
	std::vector<int> result;
	result.resize(fNum.getSize());
	int countB = sNum.getSize() - 1;
	int countA = fNum.getSize() - 1;


	for (size_t it = 0; it < fNum.getNumber().size(); it++)
	{
		result[it] = fNum.getNumber()[it];
	}
	while (countB >= 0)
	{
		int localCountA = countA - 1;
		if (result[countA] >= sNum.getValue(countB))
		{
			result[countA] = result[countA] - sNum.getValue(countB);
		}
		else
		{
			while (result[localCountA] == 0)
			{
				--localCountA;
			}
			if (result[localCountA] != 1)
			{
				result[localCountA] -= 1;
				int lCountA = localCountA + 1;
				while (fNum.getValue(lCountA) == 0)
				{
					result[lCountA] = 9;
					++lCountA;
				}
				result[countA] = result[countA] + 10 - sNum.getValue(countB);
			}
			else
			{
				result[localCountA] = 0;
				while (localCountA != countA - 1)
				{
					++localCountA;
					result[countA] = 9;
				}
				result[countA] = result[countA] + 10 - sNum.getValue(countB);
			}
		}
		--countA;
		--countB;
	}
	CLongNumber res(result);
	res.setDenialSign(a < b);
	return res;
}

CLongNumber const operator/(const CLongNumber & a, const CLongNumber & b)
{
	std::vector<int> result;
	if ((b.getSize() == 1 && b.getValue(0) == 0) || a.getSize() == 0)
	{
		result.clear();
	}
	else if (a < b)
	{
		result.push_back(0);
	}
	else if (a == b)
	{
		result.push_back(1);
	}
	else
	{
		int countB = b.getSize() - 1;
		int countA = a.getSize() - 1;
		int countNum = 0;

		std::vector<int> longNum;
		for (int i = 0; i <= countB; i++)
		{
			countNum++;
			longNum.push_back(a.getValue(i));
		}
		CLongNumber fNum(longNum);;

		
		if (fNum < b)
		{
			countNum++;
			longNum.push_back(a.getValue(countNum - 1));
		}
		
		fNum = CLongNumber(longNum);
		CLongNumber rNum = fNum - b;
		int num = 2;
		while (num < 10 && !rNum.getSign())
		{
			std::vector<int> muv = { num };
			CLongNumber muvNum(muv);
			rNum = fNum - b * muvNum;
			num++;
		}
		if (rNum.getSign())
		{
			num -= 2;
			std::vector<int> muv = { num };
			CLongNumber muvNum(muv);
			rNum = fNum - b * muvNum;
		}
		
		if (num == 10)
		{
			num--; 
		}
		std::vector<int> modNum;

		for (int i = 0; i < rNum.getSize(); i++)
		{
			modNum.push_back(rNum.getValue(i));
		}
		for (int i = countNum; i <= countA; i++)
		{
			modNum.push_back(a.getValue(i));
		}
		CLongNumber longMod(modNum);
		
		result.push_back(num);

		if (rNum.getSize() == 0)
		{
			if (b.getSize() > 1)
			{
				result.push_back(0);
			}
		}
		
		CLongNumber resDiv = longMod / b;
		if (resDiv.getValue(0) != 0)
		{
			for (int i = 0; i < resDiv.getSize(); i++)
			{
				result.push_back(resDiv.getValue(i));
			}
		}
	}
	CLongNumber res(result);
	return res;
}
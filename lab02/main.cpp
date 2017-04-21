#include <iostream>
#include <fstream>
#include "Definition.h"
#include "LongNumber.h"

std::vector<Numbers> ReadFile(const std::string & nameFile)
{
	std::ifstream inpFile(nameFile);
	if (!inpFile.is_open())
	{
		std::cout << "File not found!";
		exit(1);
	}

	std::vector<Numbers> nums;
	int num;
	while (!inpFile.eof())
	{
		bool numStr = false;
		Numbers numbers;
		std::string mainString;
		std::getline(inpFile, mainString);
		for (size_t i = 0; i < mainString.size(); i++)
		{
			if (mainString[i] == '+')
			{
				numbers.operand = Operand::Inc;
				numStr = true;
			}
			else if (mainString[i] == '-')
			{
				numbers.operand = Operand::Sub;
				numStr = true;
			}
			else if (mainString[i] == '/')
			{
				numbers.operand = Operand::Div;
				numStr = true;
			}
			else if (mainString[i] == '*')
			{
				numbers.operand = Operand::Mul;
				numStr = true;
			}
			else if (mainString[i] >= '0' && mainString[i] <= '9')
			{
				num = mainString[i] - '0';
				if (!numStr)
				{
					numbers.M.push_back(num);	
				}
				else if (numStr)
				{
					numbers.N.push_back(num);
				}
			}
		}
		
		nums.push_back(numbers);
	}
	return nums;
}

void Calculator(const std::string & inputFileName, const std::string & outFileName)
{
	std::ofstream outFile(outFileName);
	std::vector<Numbers> nums = ReadFile(inputFileName);
	CLongNumber res;
	for (auto it : nums)
	{
		CLongNumber fNum(it.M);
		CLongNumber sNum(it.N);
		switch (it.operand)
		{
		case Operand::Inc:
			res = fNum + sNum;
			break;
		case Operand::Sub:
			res = fNum - sNum;
			break;
		case Operand::Mul:
			res = fNum * sNum;
			break;
		case Operand::Div:
			res = fNum / sNum;
			break;

		default:
			res = fNum + sNum;
			break;
		}
		if (res.getSize() == 0)
		{
			outFile << "error: division to zero";
		}
		else
		{
			for (auto it : res.getNumber())
			{
				outFile << it;
			}
		}

		outFile << "\n";
	}
}

int main()
{
	std::string inputFileName;
	std::cout << "Enter input file" << std::endl;
	std::cin >> inputFileName;
	std::string outFileName;
	std::cout << "Enter input file" << std::endl;
	std::cin >> outFileName;


	Calculator(inputFileName, outFileName);
	
	system("pause");
	return 0;
}
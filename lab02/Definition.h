#pragma once
#include <string>
#include <vector>


enum class Operand
{
	Inc,
	Sub,
	Div,
	Mul
};

struct Numbers
{
	std::vector<int> M;
	Operand operand = Operand::Inc;
	std::vector<int> N;
};

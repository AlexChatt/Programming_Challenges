#include "recursive.h"

int RecursiveSum(std::vector<int> numbers)
{
	if (numbers.size() == 0)
	{
		return 0;
	}
	else
	{
		return numbers[0] + RecursiveSum(std::vector<int>(numbers.begin() +1, numbers.end()));
	}

	return 0;
}

int RecursiveCount(std::vector<int> numbers)
{
	if (numbers.size() == 0)
	{
		return 0;
	}
	else
	{
		return 1 + RecursiveCount(std::vector<int>(numbers.begin() + 1, numbers.end()));
	}
}

int RecursiveFindMax(std::vector<int> numbers)
{
	if (numbers.size() == 0)
	{
		return 0;
	}
	else
	{
		int maxNum = RecursiveFindMax(std::vector<int>(numbers.begin() + 1, numbers.end()));
		if (numbers[0] > maxNum) return numbers[0];
		else return maxNum;
	}
}

int runRecurFunctions()
{
	int TotalSum = RecursiveSum(std::vector<int>{2, 4, 6});
	int TotalCount = RecursiveCount(std::vector<int>{1,1,1,1,1,1,1});
	int MaxNum = RecursiveFindMax(std::vector<int>{2, 53, 6, 10, 2});

	return 0;
}
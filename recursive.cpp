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

std::vector<int> QuickSort(std::vector<int> numbers)
{
	std::vector<int> LessNum, MoreNums;

	if (numbers.size() < 2)
	{
		return numbers;
	}

	int pivot = rand() % numbers.size();

	for (int i = 0; i < numbers.size(); i++)
	{
		if (i == pivot)
		{
			continue;
		}
		if (numbers[i] > numbers[pivot])
		{
			MoreNums.push_back(numbers[i]);
		}
		else
		{
			LessNum.push_back(numbers[i]);
		}
	}

	std::vector<int> SortVect = QuickSort(LessNum);
	SortVect.push_back(numbers[pivot]);
	std::vector<int> moreSort = QuickSort(MoreNums);
	SortVect.insert(SortVect.end(), moreSort.begin(), moreSort.end());
	return SortVect;
	
}

int runRecurFunctions()
{
	int TotalSum = RecursiveSum(std::vector<int>{2, 4, 6});
	int TotalCount = RecursiveCount(std::vector<int>{1,1,1,1,1,1,1});
	int MaxNum = RecursiveFindMax(std::vector<int>{2, 53, 6, 10, 2});

	srand(time(NULL));
	std::vector<int> sortedNums = QuickSort(std::vector<int>{5, 10, 1, 32, 21, 4});


	return 0;
}
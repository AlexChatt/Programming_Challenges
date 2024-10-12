#pragma once
#include <vector>
#include <iterator>

enum Direction
{
	left = 0,
	right = 1,
	down = 2,
	up = 3
};

class Martix
{
private:
	int rowSize, colSize;
	std::vector<std::vector<float>> martix;

public:
	Martix();
	Martix(int rows, int cols, std::vector<float> nums);
	Martix(int rows, int cols, std::vector<std::vector<float>> newMartix);

	void SpiralInsert(std::vector<float> nums, const int rows, const int cols);
	void PrintMartix();
	void PrintSpiral();
	void PrintDiag();
	void ZeroChangeMartix();
	int FindMaxValue();
	std::vector<float> findRowCommon();
	int FindNumAtSortedIndex(int index);
	void Reset();
};

Martix::Martix()
{
	rowSize = 0;
	colSize = 0;
}

Martix::Martix(int rows, int cols, std::vector<float> nums)
{
	rowSize = rows;
	colSize = cols;
	for (int i = 0; i < nums.size(); i+=cols)
	{
		std::vector<float>::const_iterator start = nums.begin() + i;
		std::vector<float>::const_iterator end = start + cols;
		std::vector<float> Line(start, end);
		martix.push_back(Line);
	}

}

Martix::Martix(int rows, int cols, std::vector<std::vector<float>> newMartix) 
{
	rowSize = rows;
	colSize = cols;
	martix = newMartix;
}

void Martix::SpiralInsert(std::vector<float> nums, const int rows, const int cols)
{
	Direction PrintDir = Direction::right;
	int LeftBound = 0, UpBound = 0, index = 0;
	int RightBound = cols, DownBound = rows;

	rowSize = rows, colSize = cols;

	if (nums.size() != (rows * cols))
	{
		// invalid size
		return;
	}

	for (int i = 0; i < rows; i++)
	{
		std::vector<float> Insert;
		Insert.resize(rows);
		martix.push_back(Insert);
	}

	while (true)
	{
		switch (PrintDir)
		{
		case left:
			for (int i = RightBound - 1; i >= LeftBound; i--)
			{
				martix[DownBound - 1][i] = nums[index];
				index++;
			}
			PrintDir = Direction::up;
			DownBound--;
			break;
		case right:
			for (int i = LeftBound; i < RightBound; i++)
			{
				martix[UpBound][i] = nums[index];
				index++;
			}
			PrintDir = Direction::down;
			UpBound++;
			break;

		case down:
			for (int i = UpBound; i < DownBound; i++)
			{
				martix[i][RightBound - 1] = nums[index];
				index++;
			}
			PrintDir = Direction::left;
			RightBound--;
			break;
		case up:
			for (int i = DownBound - 1; i >= UpBound; i--)
			{
				martix[i][LeftBound] = nums[index];
				index++;
			}
			PrintDir = Direction::right;
			LeftBound++;
			break;
		default:
			break;
		}

		if (RightBound <= LeftBound &&
			DownBound <= UpBound)
		{
			break;
		}
	}
}

void Martix::PrintMartix()
{
	for (int i = 0; i < martix.size(); i++)
	{
		std::cout << "[ ";
		for (int j = 0; j < martix.size(); j++)
		{
			std::cout << martix[i][j] << " ";
		}
		std::cout << "]" << std::endl;
	}
}

void Martix::PrintSpiral()
{
	Direction PrintDir = Direction::right;
	int LeftBound = 0, RightBound = colSize, UpBound = 0, DownBound = rowSize;

	while (true)
	{
		switch (PrintDir)
		{
		case left:
			for (int i = RightBound - 1; i >= LeftBound; i--)
			{
				std::cout << martix[DownBound - 1][i] << " ";
			}
			PrintDir = Direction::up;
			DownBound--;
			break;
		case right:
			for (int i = LeftBound; i < RightBound; i++)
			{
				std::cout << martix[UpBound][i] << " ";
			}
			PrintDir = Direction::down;
			UpBound++;
			break;

		case down:
			for (int i = UpBound; i < DownBound; i++)
			{
				std::cout << martix[i][RightBound - 1] << " ";
			}
			PrintDir = Direction::left;
			RightBound--;
			break;
		case up:
			for (int i = DownBound - 1; i >= UpBound; i--)
			{
				std::cout << martix[i][LeftBound] << " ";
			}
			PrintDir = Direction::right;
			LeftBound++;
			break;
		default:
			break;
		}

		if (RightBound <= LeftBound &&
			DownBound <= UpBound)
		{
			break;
		}
	}

	std::cout << std::endl;

}

void Martix::PrintDiag()
{
	if (martix.size() < 1)
	{
		return;
	}

	bool increaseIndex = true;
	int x = 0, y = 0;
	std::pair<int, int> startpoint = { 0,0 };

	while (y != martix.size())
	{
		do
		{
			std::cout << martix[x][y];

			x--;
			y++;

		} while ((x >= 0 && x < martix.size()) &&
			(y >= 0 && y < martix[0].size()));

		std::cout << std::endl;

		if (increaseIndex)
		{
			x = ++startpoint.first;
			y = 0;

			if (x >= martix[0].size())
			{
				increaseIndex = false;
				x = --startpoint.first;
				y = ++startpoint.second;
			}
		}
		else
		{
			y = ++startpoint.second;
			x = startpoint.first;
		}
	}
}

void Martix::ZeroChangeMartix()
{
	std::set<int> ColsWith0;
	bool RowHasZero = false;

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < colSize; j++)
		{
			if (martix[i][j] == 0)
			{
				RowHasZero = true;
				ColsWith0.insert(j);
			}
		}
		if (RowHasZero)
		{
			martix[i].clear();
			martix[i].insert(martix[i].begin(), colSize, 0);
			RowHasZero = false;
		}
	}

	for (int i = 0; i < colSize; i++)
	{
		if (ColsWith0.find(i) != ColsWith0.end())
		{
			for (int j = 0; j < rowSize; j++)
			{
				martix[j][i] = 0;
			}
		}
	}
	std::cout << std::endl;
}

int Martix::FindMaxValue()
{
	// base case
	if (martix.size() == 0) {
		return 0;
	}

	// `K[i][j]` stores a maximum of elements in the matrix from `(i, j)`
	// to `(rowSize-1, rowSize-1)`
	std::vector<std::vector<float>> K;
	K.resize(rowSize);
	for(auto &row : K)
	{
		row.resize(rowSize);
	}

	// last element of `K[][]` will be the same as that of the specified matrix
	K[rowSize - 1][rowSize - 1] = martix[rowSize - 1][rowSize - 1];

	int max = martix[rowSize - 1][rowSize - 1];  // Initialize max

	// preprocess the last row
	for (int j = rowSize - 2; j >= 0; j--)
	{
		if (martix[rowSize - 1][j] > max) {
			max = martix[rowSize - 1][j];
		}
		K[rowSize - 1][j] = max;
	}

	max = martix[rowSize - 1][rowSize - 1];    // Initialize max

	// preprocess the last column
	for (int i = rowSize - 2; i >= 0; i--)
	{
		if (martix[i][rowSize - 1] > max) {
			max = martix[i][rowSize - 1];
		}
		K[i][rowSize - 1] = max;
	}

	max = INT_MIN;            // Initialize max

	// preprocess the rest of the matrix from the bottom
	for (int i = rowSize - 2; i >= 0; i--)
	{
		for (int j = rowSize - 2; j >= 0; j--)
		{
			// update the max value
			if (K[i + 1][j + 1] - martix[i][j] > max) {
				max = K[i + 1][j + 1] - martix[i][j];
			}

			// assign `K[i][j]`
			K[i][j] = std::max(martix[i][j], std::max(K[i][j + 1], K[i + 1][j]));
		}
	}

	return max;
}

std::vector<float> Martix::findRowCommon()
{
	std::unordered_map<int, int> numbers;
	std::vector<float> common;

	if (martix.size() < 1 || martix[0].size() < 1)
	{
		return { -1 };
	}

	for (int i = 0; i < colSize; i++)
	{
		numbers[martix[0][i]] = 0;
	}

	for (int x = 1; x < rowSize; x++)
	{
		for (int y = 0; y < colSize; y++)
		{
			if (numbers.find(martix[x][y]) != numbers.end())
			{
				numbers[martix[x][y]]++;
			}
		}

		for (std::unordered_map<int, int>::iterator it = numbers.begin(); it != numbers.end();)
		{
			if (it->second < x)
			{
				it = numbers.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	for (auto m : numbers)
	{
		common.push_back(m.first);
	}

	return common;
}

int Martix::FindNumAtSortedIndex(int index)
{
	std::multiset<int> OrderedMartix;

	// This is the quick "libs" way to do it
	for (int i = 0; i < rowSize; i++)
	{
		OrderedMartix.insert(martix[i].begin(), martix[i].end());
	}
	std::multiset<int>::iterator it = OrderedMartix.begin();
	std::advance(it, index);
	return *it;
}

void Martix::Reset()
{
	rowSize = 0;
	colSize = 0;
	martix.clear();
}

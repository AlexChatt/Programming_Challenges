#include "Hard_Algorithms.h"

int FindIndexMaxLenght(std::vector<int> numbers)
{
	int maxSize = -1;
	int currentSize = 0;
	int index = 0, maxIndex = -1;

	if (numbers.size() < 0)
	{
		return -1;
	}

	for (int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] == 1)
		{
			currentSize++;
		}
		else
		{
			currentSize = i - index;
			index = i;
		}

		if (currentSize > maxSize)
		{
			maxSize = currentSize;
			maxIndex = index;
		}
	}

	return maxIndex;
}

int MaxSumInCirArray(std::vector<int> numbers)
{
	int CminI = 0;
	int minI = 0, maxI = 0;
	bool Overlap = false;

	int MaxSubValue, CMax;
	int index = 0;

	if (numbers.size() < 1)
	{
		return 0;
	}

	MaxSubValue = CMax = numbers[0];

	while (true)
	{
		index++;
		if (index == numbers.size())
		{
			index=0;
			Overlap = true;
		}

		if (CMax + numbers[index] < numbers[index])
		{
			if (Overlap)
			{
				break;
			}

			int temp = CMax;
			while (CMax <= temp && CminI != index)
			{
				CMax -= numbers[CminI];
				CminI++;
			}
		}

		CMax += numbers[index];

		if (CMax > MaxSubValue)
		{
			minI = CminI;
			maxI = index;
			MaxSubValue = CMax;
		}
		else if (Overlap)
		{
			break;
		}
	}
	
	return MaxSubValue;
}

int MaxProductSubarray(std::vector<int> numbers)
{
	int MaxSum, CurrentMax, MinSum;

	if (numbers.size() < 1)
	{
		return 0;
	}

	MaxSum = CurrentMax = MinSum = numbers[0];

	for (int i = 1; i < numbers.size(); i++)
	{
		int OldCurrentMax = CurrentMax;
		CurrentMax = std::max(numbers[i], std::max(numbers[i] * CurrentMax, numbers[i] * MinSum));
		MinSum = std::min(numbers[i], std::min(numbers[i] * OldCurrentMax, numbers[i] * MinSum));
		MaxSum = std::max(MaxSum, CurrentMax);
	}

	return MaxSum;
}

int GetTrappedRainAmount(std::vector<int> numbers)
{
	int StartBarIndex;
	int RainAmount = 0;

	if (numbers.size() < 2)
	{
		return 0;
	}

	StartBarIndex = numbers.size()-1;

	for (int i = numbers.size() - 2; i >= 0; i--)
	{
		if (numbers[i] >= numbers[StartBarIndex] || i == 0)
		{
			//int WaterMax = std::min(numbers[i], numbers[StartBarIndex]);
			//int j = i+1;
			//while (j < StartBarIndex)
			//{
			//	RainAmount += (WaterMax - numbers[j]);
			//	j++;
			//}
			StartBarIndex = i;
		}
		else
		{
			RainAmount += numbers[StartBarIndex] - numbers[i];
		}
	}

	return RainAmount;
}

int LongestLengthSameSum(std::vector<int> X, std::vector<int> Y)
{
	std::unordered_map<int, int> MatchCount;

	int CurX = 0, CurY = 0;
	int result = 0;

	MatchCount[0] = -1;

	for (int i = 0; i < X.size(); i++)
	{
		CurX += X[i];
		CurY += Y[i];

		int diff = CurX - CurY;

		if (MatchCount.find(diff) == MatchCount.end())
		{
			MatchCount[diff] = i;
		}
		else
		{
			result = std::max(result, i - MatchCount[diff]);
		}
	}

	return result;
}

// Function to rearrange an array such that `A[A[i]]` is set to `i`
// for every element `A[i]`
void InPlaceArrange(std::vector<int>& numbers)
{
	// for each element `numbers[i]`, increment value present at index
    // `(numbers[i] % numbers.size())` by `i×numbers.size()`
	for (int i = 0; i < numbers.size(); i++) {
		int remain = numbers[i] % numbers.size();
		numbers[remain] += i * numbers.size();
	}

	// traverse the modified array and set `numbers[i] = numbers[i]/numbers.size()`
	for (int i = 0; i < numbers.size(); i++) {
		numbers[i] /= numbers.size();
	}
}

int FindMaxDiffSubArrays(std::vector<int> numbers)
{
	int MaxStart = -1, MaxEnd = -1;
	int MinStart = -1, MinEnd = -1;
	bool bMaxBigger = false;

	int MaxSubArrayVal = GetMinOrMaxNum(numbers, MaxStart, MaxEnd, true);
	int MinSubArrayVal = GetMinOrMaxNum(numbers, MinStart, MinEnd, false);

	if ((MinStart < MaxStart && MinEnd < MaxStart) ||
		(MaxStart < MinStart && MaxEnd < MinStart))
	{
		return MaxSubArrayVal - MinSubArrayVal;
	}

	if (MaxSubArrayVal >= std::abs(MinSubArrayVal))
	{
		bMaxBigger = true;
	}

	if (bMaxBigger)
	{
		MinSubArrayVal = GetMinOrMaxNum(numbers, MaxStart, MaxEnd, false);
	}
	else
	{
		MaxSubArrayVal = GetMinOrMaxNum(numbers, MinStart, MinEnd, true);
	}

	return MaxSubArrayVal - abs(MinSubArrayVal);
}

int GetMinOrMaxNum(std::vector<int> numbers, int &RestrictStart, int &RestrictEnd, bool bFindMax)
{
	int TotalSum = INT_MAX, CurrentSum = 0;
	int CurrentRS = 0;
	bool bSetRestrict = false;

	if (bFindMax) { TotalSum = -INT_MAX; }

	if (RestrictStart == -1)
	{
		bSetRestrict = true;
	}
	
	for (int i = 0; i < numbers.size(); i++)
	{
		CurrentSum += numbers[i];

		if (bFindMax)
		{
			CurrentSum = std::max(CurrentSum, numbers[i]);
			TotalSum = std::max(TotalSum, CurrentSum);
		}
		else
		{
			CurrentSum = std::min(CurrentSum, numbers[i]);
			TotalSum = std::min(TotalSum, CurrentSum);
		}

		if (CurrentSum == numbers[i] && bSetRestrict)
		{
			CurrentRS = i;
		}

		if (TotalSum == CurrentSum && bSetRestrict)
		{
			RestrictEnd = i;
			RestrictStart = CurrentRS;
		}

		if (!bSetRestrict &&
			i == RestrictStart - 1)
		{
			i = RestrictEnd;
			CurrentSum = 0;
		}
	}

	return TotalSum;
}

std::vector<std::vector<int>> GetAllPosCombos(int N) 
{
	std::vector<std::vector<int>> Combos;
	std::vector<int> CurList;

	FillCombos(Combos, N, 0, CurList);

	return Combos;
}

void FillCombos(std::vector<std::vector<int>>& combos, int N, int Sum, std::vector<int> currentList)
{
	int minNumber = 1;

	if (Sum == N)
	{
		combos.push_back(currentList);
		return;
	}
	else if (Sum > N)
	{
		return;
	}

	if (currentList.size() > 0) {
		minNumber = currentList[currentList.size()-1];
	}

	for (int i = minNumber; i <= N; i++)
	{
		currentList.push_back(i);
		FillCombos(combos, N, Sum + i, currentList);
		currentList.pop_back();
	}

}

std::pair<int, int> FindMinRange3(std::vector<int> n1, std::vector<int> n2, std::vector<int> n3)
{
	std::pair<int, int> range;
	int MinDiff = INT_MAX;
	int n1i = 0, n2i = 0, n3i = 0;

	while (n1i < n1.size() && n2i < n2.size() && n3i < n3.size())
	{
		int curMin = std::min(n1[n1i], std::min(n2[n2i], n3[n3i]));
		int curMax = std::max(n1[n1i], std::max(n2[n2i], n3[n3i]));
		int tempmin = curMax - curMin;

		if (tempmin < MinDiff)
		{
			range = std::pair<int, int>( curMin,curMax );
			MinDiff = tempmin;
		}

		int n1diff = INT_MAX, n2diff = INT_MAX, n3diff = INT_MAX;

		if (n1i + 1 < n1.size())
		{
			n1diff = std::abs(n1[n1i + 1] - n2[n2i]) +
				std::abs(n1[n1i + 1] - n3[n3i]);
		}
		if (n2i + 1 < n2.size())
		{
			n2diff = std::abs(n2[n2i + 1] - n1[n1i]) +
				std::abs(n2[n2i + 1] - n3[n3i]);
		}
		if (n3i + 1 < n3.size())
		{
			n3diff = std::abs(n3[n3i + 1] - n1[n1i]) +
				std::abs(n3[n3i + 1] - n2[n2i]);
		}

		int Mindiff = std::min(n1diff, std::min(n2diff, n3diff));

		if (Mindiff == n1diff) { n1i++; }
		else if (Mindiff == n2diff) { n2i++; }
		else { n3i++; }
	}

	return range;
}

bool isSubsetExist(std::vector<int> const& S, int n, int a, int b, int c, std::vector<int>& arr)
{
	// return true if the subset is found
	if (a == 0 && b == 0 && c == 0) {
		return true;
	}

	// base case: no items left
	if (n < 0) {
		return false;
	}

	// Case 1. The current item becomes part of the first subset
	bool A = false;
	if (a - S[n] >= 0)
	{
		arr[n] = 1;        // current element goes to the first subset
		A = isSubsetExist(S, n - 1, a - S[n], b, c, arr);
	}

	// Case 2. The current item becomes part of the second subset
	bool B = false;
	if (!A && (b - S[n] >= 0))
	{
		arr[n] = 2;        // current element goes to the second subset
		B = isSubsetExist(S, n - 1, a, b - S[n], c, arr);
	}

	// Case 3. The current item becomes part of the third subset
	bool C = false;
	if ((!A && !B) && (c - S[n] >= 0))
	{
		arr[n] = 3;        // current element goes to the third subset
		C = isSubsetExist(S, n - 1, a, b, c - S[n], arr);
	}

	// return true if we get a solution
	return A || B || C;
}

// Function for solving the 3–partition problem. It prints the subset if
// the given set `S[0…n-1]` can be divided into three subsets with an equal sum
void partition(std::vector<int> const& S)
{
	// get the sum of all elements in the set
	int sum = accumulate(S.begin(), S.end(), 0);

	// total number of items in `S`
	int n = S.size();

	// construct an array to track the subsets
	// `arr[i] = k` represents i'th item of `S` is part of k'th subset
	std::vector<int> arr(n);

	// set result to true if the sum is divisible by 3 and the set `S` can
	// be divided into three subsets with an equal sum
	bool result = (n >= 3) && !(sum % 3) &&
		isSubsetExist(S, n - 1, sum / 3, sum / 3, sum / 3, arr);

	if (!result)
	{
		std::cout << "3-Partition of set is not possible";
		return;
	}

	// print the partitions
	for (int i = 0; i < 3; i++)
	{
		std::cout << "Partition " << i << " is ";
		for (int j = 0; j < n; j++)
		{
			if (arr[j] == i + 1) {
				std::cout << S[j] << " ";
			}
		}
		std::cout << std::endl;
	}
}

int InverseCountMergeSort(std::vector<int>& arr, std::vector<int>& aux, int low, int high)
{
	if (high <= low)
	{
		return 0;
	}

	int mid = (low + ((high - low) >> 1));
	int InverseCount = 0;

	InverseCount += InverseCountMergeSort(arr, aux, low, mid);
	InverseCount +=  InverseCountMergeSort(arr, aux, mid + 1, high);

	InverseCount += InverseCountMergeS(arr, aux, low, mid, high);

	return InverseCount;
}

int InverseCountMergeS(std::vector<int>& arr, std::vector<int>& aux, int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;
	int InverseCount = 0;

	while (i <= mid && j <= high)
	{
		if (arr[i] <= aux[j])
		{
			aux[k++] = arr[i++];
		}
		else
		{
			// we know we have already sorted the mid to low, so any 
			// number from i -> mid will be bigger then aux[j], so we
			// increase the count by that diference (mid - i + 1)
			InverseCount += (mid - i + 1);
			aux[k++] = arr[j++];
		}
	}

	while (i <= mid)
	{
		aux[k++] = arr[i++];
	}

	for (int i = low; i <= high; i++)
	{
		arr[i] = aux[i];
	}

	return InverseCount;
}

int runHFunctions()
{
	//https://www.techiedelight.com/find-index-0-replaced-get-maximum-length-sequence-of-continuous-ones/
	std::vector<int> numbers = { 0,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1 };
	int IndexToReplace = FindIndexMaxLenght(numbers);
	std::cout << "The index to replace 0 with 1 for the max 1 length is " << IndexToReplace << std::endl;
	//End

	//https://www.techiedelight.com/maximum-sum-circular-subarray/
	numbers = { 2, 1, -5, 4, -3, 1, -3, 4, -1 };
	std::cout << "The sum of the subarray with the largest sum is: " <<  MaxSumInCirArray(numbers) << std::endl;
	//End

	//https://www.techiedelight.com/find-maximum-product-subarray-given-array/
	numbers = { 40, 0, -20, -10 };
	std::cout<< "The max product in the subarray is: " << MaxProductSubarray(numbers) << std::endl;
	//End
	//Look into https://www.techiedelight.com/maximum-subarray-problem-kadanes-algorithm/ for another solution

	//https://www.techiedelight.com/trapping-rain-water-within-given-set-bars/
	// Sliding window maybe??
	numbers = { 7, 0, 4, 2, 5, 0, 6, 4, 0, 5 };
	std::cout<< "The maximum amount of water that can be trapped is " << GetTrappedRainAmount(numbers) << std::endl;
	//End

	//https://www.techiedelight.com/length-longest-continuous-sequence-same-sum-binary-arrays/
	std::vector<int> X = { 0, 0, 1, 1, 1, 1 };
	std::vector<int> Y = { 0, 1, 1, 0, 1, 0 };
	std::cout << "The length of the longest continuous sequence with the same sum is " << LongestLengthSameSum(X, Y) << std::endl;
	//End

	//https://techiedelight.com/rearrange-array-such-that-array-index-is-set-to-i/
	numbers = { 1, 3, 4, 2, 0 };
	InPlaceArrange(numbers);
	//End

	//https://www.techiedelight.com/find-maximum-absolute-difference-subarrays/
	numbers = { -3, -2, 6, -3, 5, -9, 3, 4, -1, -8, 2 };
	std::cout<<"The maximum absolute difference is: " << FindMaxDiffSubArrays(numbers) << std::endl;
	//End

	//https://www.techiedelight.com/print-combinations-integers-sum-given-number/
	std::vector<std::vector<int>> AllCombosToNum = GetAllPosCombos(5);
	//End

	//https://www.techiedelight.com/find-minimum-range-given-arrays/
	std::vector<int> n1 = { 2, 3, 4, 8, 10, 15 };
	std::vector<int> n2 = { 1, 5, 12 };
	std::vector<int> n3 = { 7, 8, 15, 16 };
	std::pair<int, int> minDiffR3 = FindMinRange3(n1, n2, n3);
	std::cout << "Minimum range is " << minDiffR3.first << "-" << minDiffR3.second << std::endl;
	//End

	//https://www.techiedelight.com/3-partition-problem-extended-print-all-partitions/
	//Uses Partition: Important one to learn and try and use elsewhere
	numbers = { 7, 3, 2, 1, 5, 4, 8 };
	partition(numbers);
	//End

	// First read https://www.techiedelight.com/merge-sort/
	//https://www.techiedelight.com/inversion-count-array/
	numbers = { 1,9,6,4,5 };
	std::vector<int> numbersCopy = numbers;
	std::cout << "The inversion count is: " << InverseCountMergeSort(numbers, numbersCopy, 0, numbers.size() - 1) << std::endl;
	//End

	//https://www.techiedelight.com/find-index-row-containing-maximum-number-1s-matrix
	//End

	//https://www.techiedelight.com/water-jugs-problem/
	//End

	//https://www.techiedelight.com/check-repeated-subsequence-present-string-not/
	//End

	//https://www.techiedelight.com/print-possible-solutions-n-queens-problem/
	//End

	//https://www.techiedelight.com/surpasser-count-each-element-array/
	//End

	return 0;
}
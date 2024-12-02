#include "Medium_Algorithms.h"
#include "Martix.h"
#include "Template_functions.h"

void swapInt(std::vector<int>& nums, int I1, int I2)
{
	int temp = nums[I1];
	nums[I1] = nums[I2];
	nums[I2] = temp;
}

void swapIntTwoVectors(std::vector<int>& nums1, std::vector<int>& nums2, int I1, int I2)
{
	int temp = nums1[I1];
	nums1[I1] = nums2[I2];
	nums2[I2] = temp;
}

bool DetectSubArrayZero(int Numbers[], int size)
{
	std::unordered_set<int> foundNumbers;
	int sum = 0;
	foundNumbers.insert(0);

	for (int i = 0; i < size; i++)
	{
		sum += Numbers[i];

		if (foundNumbers.find(sum) != foundNumbers.end())
		{
			return true;
		}
		else
		{
			foundNumbers.insert(sum);
		}
	}

	return false;
}

std::vector<int> LargestSubArrayToTarget(std::vector<int> nums, int target)
{
	std::vector<int> SubArray;
	int startingIndex = -1, endingIndex = -1;
	int subArraySize = -1;
	int sum = 0;

	// create an empty map to store the ending index of the first subarray
	// having some sum
	std::unordered_map<int, int> map;

	// insert (0, -1) pair into the set to handle the case when a
	// subarray with sum `S` starts from index 0
	map[0] = -1;

	int curSum = 0;
	// `len` stores the maximum length of subarray with sum `S`
	int len = 0;

	// traverse the given array
	for (int i = 0; i < nums.size(); i++)
	{
		// sum of elements so far
		curSum += nums[i];

		// if the sum is seen for the first time, insert the sum with its
		// into the map
		if (map.find(curSum) == map.end()) {
			map[curSum] = i;
		}

		// update length and ending index of the maximum length subarray
		// having sum `S`
		// If we can find a number after taking target away from curSum, then we can get
		// to the target with a subarray
		if (map.find(curSum - target) != map.end() && len < i - map[curSum - target])
		{
			len = i - map[curSum - target];
			endingIndex = i;
		}
	}

	// print the subarray
	for (int i = endingIndex - len + 1; i <= endingIndex; i++)
	{
		SubArray.push_back(nums[i]);
	}

	// Brute force
	/*
	for (int i = 0; i < nums.size(); i++)
	{
		sum = 0; //reset
		for (int j = i; j < nums.size(); j++)
		{
			sum += nums[j];
			if(sum == target && (j - i) > subArraySize)
			{
				startingIndex = i;
				endingIndex = j;
				subArraySize = (j - i)+1;
			}
		}
	}
	if (startingIndex != -1)
	{
		for (int i = startingIndex; i <= endingIndex; i++)
		{
			SubArray.push_back(nums[i]);
		}
	}
	*/

	return SubArray;
}

void FindAllZeroSubArrays(std::vector<int> nums)
{	
	int sum = 0;
	int target = 0;
	// Brute force
	for (int i = 0; i < nums.size(); i++)
	{
		sum = 0; //reset
		for (int j = i; j < nums.size(); j++)
		{
			sum += nums[j];
			if(sum == target)
			{
				std::cout << "0 SubArray Found: { ";
				for (int x = i; x <= j; x++)
				{
					std::cout << nums[x] << " ";
				}
				std::cout << "}\n";
			}
		}
	}
}

void Sort012Array(std::vector<int>& nums)
{
	int low = 0, high = nums.size() - 1;
	int mid = 0;

	while (mid <= high)
	{
		if (nums[mid] < 1)
		{
			swapInt(nums, low, mid);
			low++;
			mid++;
		}
		else if (nums[mid] > 1)
		{
			swapInt(nums, mid, high);
			high--;
		}
		else
		{
			mid++;
		}
	}
}

void inPlaceTwoArrayMerge(std::vector<int>& nums1, std::vector<int>& nums2)
{
	for (int i = 0; i < nums1.size(); i++)
	{
		if (nums1[i] > nums2[0])
		{
			swapIntTwoVectors(nums1, nums2, i, 0);			
			for (int j = 1; j < nums2.size(); j++)
			{
				if (nums2[j] < nums2[j - 1])
				{
					swapInt(nums2, j, j-1);
				}
			}
		}
	}
}

void inPlaceTwoArrayMergeConstraints(std::vector<int>& nums1, std::vector<int>& nums2)
{
	int constraint = 0;
	int N2Pos = 0;
	bool bAllZerosLeft = false;

	for (int i = 0; i < nums1.size()-1 || N2Pos < nums2.size(); i++)
	{
		if (nums1[i] == constraint)
		{
			bAllZerosLeft = true;
			for (int j = i + 1; j < nums1.size(); j++)
			{
				if (nums1[j] < nums2[N2Pos])
				{
					if (nums1[j] != constraint)
					{
						swapInt(nums1, i, j);
						bAllZerosLeft = false;
						break;
					}
				}
				else
				{
					swapIntTwoVectors(nums1, nums2, i, N2Pos);
					N2Pos++;
					bAllZerosLeft = false;
				    break;
				}
			}

			if (bAllZerosLeft)
			{
				while (N2Pos < nums2.size())
				{
					swapIntTwoVectors(nums1, nums2, i, N2Pos);
					i++;
					N2Pos++;
				}
			}
		}
	}
}

void largestSubarray01(std::vector<int>& nums)
{
	// create an empty map to store the ending index of the first subarray
    // having some sum
	std::unordered_map<int, int> map;

	// insert (0, -1) pair into the set to handle the case when a
	// subarray with zero-sum starts from index 0
	map[0] = -1;

	// `len` stores the maximum length of subarray with zero-sum
	int len = 0;

	// stores ending index of the largest subarray having zero-sum
	int ending_index = -1;

	int sum = 0;

	// Traverse through the given array
	for (int i = 0; i < nums.size(); i++)
	{
		// sum of elements so far (replace 0 with -1)
		sum += (nums[i] == 0) ? -1 : 1;

		// if the sum is seen before
		if (map.find(sum) != map.end())
		{
			// update length and ending index of largest subarray having zero-sum
			if (len < i - map[sum])
			{
				len = i - map[sum];
				ending_index = i;
			}
		}
		// if the sum is seen for the first time, insert the sum with its
		// index into the map
		else {
			map[sum] = i;
		}
	}

	// print the subarray if present
	if (ending_index != -1) {
		std::cout << "largestSubarray01: [" << ending_index - len + 1 << ", " << ending_index << "]" << std::endl;
	}
	else {
		std::cout << "No subarray exists" << std::endl;
	}
}

void ProductReplace(std::vector<int>& nums)
{
	std::vector<int> right;
	int sum = 1;
	right.push_back(sum);
	for (int i = nums.size() - 1; i >= 1; i--)
	{
		sum = sum * nums[i];
		right.push_back(sum);
	}
	sum = 1;

	for (int i = 0; i < nums.size(); i++)
	{
		int temp = nums[i];
		nums[i] = sum * right[nums.size() - 1 - i];
		sum = sum * temp;
	}

	std::cout << "ProductReplace: Array = { ";
	for (auto i : nums) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
}

void largestsubarrayConInts(std::vector<int> nums)
{
	int HighestMax = -INT32_MAX;
	int CurrentMax = 0;
	int StartIndex = 0;
	int EndingIndex = 0;
	bool ForceCheck = false;
	std::set<int> numberSee;

	//refactored answer
	for (int i = 0; i < nums.size(); i++)
	{
		numberSee.clear();
		CurrentMax = nums[i];
		numberSee.insert(nums[i]);

		if (nums[i] > HighestMax)
		{
			HighestMax = nums[i];
			StartIndex = EndingIndex = i;
		}

		for (int j = i + 1; j < nums.size(); j++)
		{
			if (numberSee.find(nums[j]) != numberSee.end())
			{
				break;
			}

			int test = *--numberSee.end() - *numberSee.begin();

			CurrentMax += nums[j];
			numberSee.insert(nums[j]);

			if (CurrentMax > HighestMax &&
				(*--numberSee.end() - *numberSee.begin() == (j - i)))
			{
				StartIndex = i;
				EndingIndex = j;
				HighestMax = CurrentMax;
			}
		}
	}

	/*
	* first attempt
		for (int i = 0; i < nums.size(); i++)
	{
		numberSee.clear();
		CurrentMax = nums[i];
		numberSee.insert(nums[i]);

		if (nums[i] > HighestMax)
		{
			HighestMax = nums[i];
			StartIndex = EndingIndex = i;
		}

		for (int j = i + 1; j < nums.size(); j++)
		{
			if (numberSee.find(nums[j]) != numberSee.end() || ForceCheck)
			{
				if (CurrentMax > HighestMax &&
					(*--numberSee.end() - *numberSee.begin() == (j - i - 1)))
				{
					StartIndex = i;
					EndingIndex = --j;
					HighestMax = CurrentMax;
				}
				ForceCheck = false;
				break;
			}
			else
			{
				CurrentMax += nums[j];
				numberSee.insert(nums[j]);

				if (j == nums.size() - 1)
				{
					ForceCheck = true;
					if (*--numberSee.end() - *numberSee.begin() == (j - i))
					{
						if (CurrentMax > HighestMax)
						{
							StartIndex = i;
							EndingIndex = j;
							HighestMax = CurrentMax;
						}
					}
					else
					{
						CurrentMax -= nums[j];
						numberSee.erase(nums[j]);
						j--;
					}
				}
			}
		}
	}
	
	*/

	std::cout << "Largest consecutive SubArray is [" << StartIndex << "," << EndingIndex << "]" << std::endl;
}

void FindMaxDiff(std::vector<int> nums)
{
	int minNumber = INT_MAX;
	int maxDiff = 0;

	if (nums.size() <= 1)
	{
		std::cout << "no diff can be given";
		return;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] < minNumber)
		{
			minNumber = nums[i];
		}
		if ((nums[i] - minNumber) > maxDiff)
		{
			maxDiff = nums[i] - minNumber;
		}
	}

	std::cout << "The maximum difference is: " << maxDiff << "\n";
}

void LongestBitonicSubArray(std::vector<int> nums)
{
	int maxBitonicCount = 0, currentBitonicCount = 0;
	int ABitonicCount = 0, DeBitonicCount = 0;
	int startingIndex = 0, endingIndex = 0;

	if (nums.size() <= 1)
	{
		std::cout << "array size is 0 or 1 (LongestBitonicSubArray)\n";
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (i + 1 >= nums.size() || nums[i + 1] > nums[i])
		{
			if (DeBitonicCount > 0)
			{
				int newMax = currentBitonicCount + DeBitonicCount;
				if (newMax > maxBitonicCount)
				{
					startingIndex = i - newMax;
					endingIndex = i;
					maxBitonicCount = newMax;
				}
				DeBitonicCount = 0;
			}
			ABitonicCount++;
		}
		else
		{
			if (ABitonicCount > 0)
			{
				currentBitonicCount = ABitonicCount;
				ABitonicCount = 0;
			}
			DeBitonicCount++;
		}
	}

	if (ABitonicCount == nums.size())
	{
		std::cout << "All numbers within the array are in Acending order\n";
	}
	else if (DeBitonicCount == nums.size())
	{
		std::cout << "All numbers within the array are in Descending order\n";
	}
	else
	{
		std::cout << "Longest bitonic subarray of the sequence is { ";
		for (int i = startingIndex; i <= endingIndex; i++)
		{
			std::cout << nums[i] << " ";
		}
		std::cout << "}\n";
	}
}

void FindMaxContinuesSubArray(std::vector<int> nums)
{
	int startingIndex = 0, endingIndex = 0;
	int maxFound = INT32_MIN;
	int curretMax = 0;
	
	for (int i = 0; i < nums.size(); i++)
	{
		curretMax += nums[i];

		if (curretMax < nums[i])
		{
			if (curretMax > maxFound)
			{
				maxFound = curretMax;
				curretMax = nums[i];
			}
			startingIndex = i;
		}

		if (curretMax > maxFound)
		{
			endingIndex = i;
			maxFound = curretMax;
		}
	}

	std::cout << "Largest subarray is { ";
	for (int i = startingIndex; i <= endingIndex; i++)
	{
		std::cout << nums[i] << " ";
	}
	std::cout << "}, which has a max value of " << maxFound << "\n";
}

void MaxSequeceOnes(std::vector<int> nums, int k)
{
	int start = 0, end = 0;
	int biggestSequence = 0;
	int zeroCount = 0;

	for (int low = 0, high = 0; high < nums.size(); high++)
	{
		if (nums[high] == 0)
		{
			zeroCount++;
		}

		if (zeroCount > k)
		{
			if ((high - 1) - low > biggestSequence)
			{
				start = low;
				end = high - 1;
				biggestSequence = high - low;
			}

			while (zeroCount > k)
			{
				if (nums[low] == 0)
				{
					zeroCount--;
				}
				low++;
			}
		}
	}

	std::cout << "Largest sequence with " << k << " replaceable 0's is { ";
	for (int i = start; i <= end; i++)
	{
		std::cout << nums[i] << " ";
	}
	std::cout << "}, which is of size " << biggestSequence << "\n";
	
}

void PrintAllCombos(std::vector<int> nums, int k)
{
	std::vector<std::vector<int>> combos;
	std::unordered_map<std::string,int> duptracker;
	std::string combostring;
	int previousJ = 1;

	for (int i = 0; i < nums.size(); i++)
	{
		std::vector<int> newCombo;
		newCombo.push_back(nums[i]);
		combostring = std::to_string(nums[i]);
		previousJ = i + 1;

		if (i + k > nums.size()) { break; }

		for (int j = previousJ; j < nums.size(); j++)
		{
			newCombo.push_back(nums[j]);
			combostring += std::to_string(nums[j]);

			if (newCombo.size() == k && duptracker.find(combostring) == duptracker.end())
			{
				combos.push_back(newCombo);
				newCombo.clear();
				newCombo.push_back(nums[i]);
				j = previousJ;
				previousJ = j+1;
				duptracker.insert({ combostring, 1 });
				combostring = std::to_string(nums[i]);
			}
		}
	}

	std::cout << "Combos found (PrintAllCombos): ";
	for (int i = 0; i < combos.size(); i++)
	{
		printVector(combos[i]);
		std::cout << " ";
	}
	std::cout << "\n";
}

void FindMinSubArrayOfSize(std::vector<int> nums, int k)
{
	int minSum = INT_MAX, currentSum = 0;
	int low = 0, high = 0;
	int currentLow = 0, currentk = 0;

	for (int i = 0; i < nums.size(); i++)
	{
		currentSum += nums[i];
		currentk++;

		if (currentk >= k)
		{
			if (currentSum < minSum)
			{
				low = currentLow;
				high = low + k - 1;
				minSum = currentSum;
			}

			currentSum -= nums[currentLow];
			currentk--;
			currentLow++;
		}
	}

	std::cout << "minimum sum subarray of size " << k << " is { ";
	for (int i = low; i <= high; i++)
	{
		std::cout << nums[i] << " ";
	}
	std::cout << "}\n";
}

void FindSubArrayWithSum(std::vector<int> nums, int target)
{
	std::map<int, int> list;
	int curretSum = 0;
	int endingI = 0;

	list.insert(std::pair<int, int>(0, -1));

	for (int i = 0; i < nums.size(); i++)
	{
		curretSum += nums[i];

		if (list.find(curretSum - target) != list.end())
		{
			endingI = i;
			break;
		}
		list.insert(std::pair<int, int>(curretSum, i));
	}

	if (list.find(curretSum - target) != list.end())
	{
		std::cout << "Found SubArray that equals " << target << ": ";
		std::cout << "[ ";
		for (int i = list[curretSum - target] + 1; i <= endingI; i++)
		{
			std::cout << nums[i] << " ";
		}
		std::cout << "]\n";
	}

}

void MaxStockProfit(std::vector<int> nums)
{
	int curretProfit = 0;
	std::vector<std::pair<int, int>> buysell;

	if (nums.size() <= 0) { return; }
	int curretSellDay = nums.size()-1;

	for (int i = nums.size() - 2; i >= 0; i--)
	{
		if (nums[i] < nums[curretSellDay])
		{
			if (!(i - 1 >= 0 && nums[i - 1] < nums[i]))
			{
				curretProfit += nums[curretSellDay] - nums[i];
				buysell.push_back(std::pair<int, int>(i + 1, curretSellDay+1));
				curretSellDay = i-1;
			}
		}
		else if (nums[i] > nums[curretSellDay])
		{
			curretSellDay = i;
		}
	}

	std::cout << "Total profit made: " << curretProfit << "\n";
	for (int i = 0; i < buysell.size(); i++)
	{
		std::cout<< "    Buy on day " << buysell[i].first << " and sell on day " << buysell[i].second << '\n';
	}

}

void MaxPlatformsNeeded(std::vector<double> arrive, std::vector<double> depart)
{
	int departIndex = 0;
	int maxPlatforms = 1, currentPlatform = 0;
	int i = 0;

	std::sort(arrive.begin(), arrive.end());
	std::sort(depart.begin(), depart.end());

	while (i < arrive.size() && departIndex < depart.size())
	{
		if (arrive[i] < depart[departIndex])
		{
			currentPlatform++;
			maxPlatforms = std::max(currentPlatform, maxPlatforms);
			i++;
		}
		else
		{
			departIndex++;
			currentPlatform--;
		}
	}

	std::cout << "Max number of platforms needed is " << maxPlatforms << "\n";
}

void SubArrayRevert(std::vector<int> nums, int SI, int EI, int m)
{
	for (int i = SI; i < EI; i += m)
	{
		if ((EI - i) + 1 < m)
		{
			break;
		}

		int start = i, end = i + m-1;
		while (end > start)
		{
			int temp = nums[start];
			nums[start] = nums[end];
			nums[end] = temp;
			start++;
			end--;
		}
	}

	for (auto i : nums) { std::cout << i << " "; }
	std::cout << "\n";
}

std::tuple<int, int, int> FindSortedTriplet(std::vector<int> nums)
{
	std::tuple<int, int, int> triplet(-1,-1,-1);
	std::vector<int> MinAtIndex(nums.size(), -1);
	std::vector<int> MaxAtIndex(nums.size(), -1);

	if (nums.size() < 3)
	{
		return triplet;
	}

	int min = INT_MAX;
	int max = -INT_MAX;

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] < min)
		{
			min = nums[i];
		}
		MinAtIndex[i] = min;
	}

	for (int i = nums.size()-1; i >= 0; i--)
	{
		if (nums[i] > max)
		{
			max = nums[i];
		}
		MaxAtIndex[i] = max;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] > MinAtIndex[i] && nums[i] < MaxAtIndex[i])
		{
			return std::make_tuple(MinAtIndex[i], nums[i], MaxAtIndex[i]);
		}
	}
}

void IncreasingSubArrays(std::vector<int> nums)
{
	std::vector<std::pair<int, int>> increaseRange;

	if (nums.size() < 2)
	{
		return;
	}

	int length = 1;
	int count = 0;

	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i - 1] < nums[i])
		{
			count += (length++);
		}
		else
		{
			length = 1;
		}
	}

	std::cout << "The total number of strictly increasing subarrays is " << count <<"\n";
}

void FindMinMovesToZero(std::vector<int> nums)
{
	int Operations = 0;
	bool bAllZero = false;

	while (!bAllZero)
	{
		bool bCanDivTwo = true;
		bAllZero = true;
		int firstNonDivIndex = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] % 2 != 0)
			{
				firstNonDivIndex = i;
				bAllZero = bCanDivTwo = false;
				break;
			}
			else if (nums[i] != 0)
			{
				bAllZero = false;
			}
		}

		if (bCanDivTwo)
		{
			for (int i = 0; i < nums.size(); i++)
			{
				nums[i] /= 2;
			}
		}
		else
		{
			nums[firstNonDivIndex]--;
		}

		if (!bAllZero)
		{
			Operations++;
		}
	}

	std::cout<< "The minimum number of moves required to convert an array {0, 0, 0} to array { " << nums[0] 
		<< ", " << nums[1] << ", " << nums[2] << " } is " << Operations << "\n";
}

void FindPairForSumInCir(std::vector<int> nums, int sum)
{
	int pivotIndex = -1;
	std::set<int> PrePivotNums;
	std::pair<int, int> SumPair(-1,-1);

	if (nums.size() == 0)
	{
		return;
	}
	PrePivotNums.insert(nums[0]);

   // first find pivot point
	for (int i = 1; i < nums.size(); i++)
	{
		if (nums[i] < nums[i - 1])
		{
			pivotIndex = i;
			break;
		}
		PrePivotNums.insert(nums[i]);
	}

	if (pivotIndex == -1)
	{
		std::cout << "No pivot point detected in circularly sorted array\n";
		return;
	}

	for (int i = pivotIndex; i < nums.size(); i++)
	{
		std::set<int>::iterator iter = PrePivotNums.find(sum - nums[i]);
		if (iter != PrePivotNums.end())
		{
			SumPair = std::pair<int,int>(nums[i], *iter);
			break;
		}
	}

	if (SumPair.first == SumPair.second)
	{
		std::cout << "No pair found for sum " << sum << "\n";
	}
	else
	{
		std::cout << "Pair: " << SumPair.first << " and " << SumPair.second << " = " << sum << "\n";
	}
}

void FindTripletToSum(std::vector<int> nums, int sum)
{
	std::map<int, int> NumsSet;

	for (int i = 0; i < nums.size(); i++)
	{
		NumsSet[nums[i]] = i;
	}

	for (int i = 0; i < nums.size(); i++)
	{
		for (int j = i + 1; j < nums.size(); j++)
		{
			int findnum = sum - (nums[i] + nums[j]);
			if (NumsSet.find(findnum) != NumsSet.end() &&
				(NumsSet[findnum] != i && NumsSet[findnum] != j))
			{
				std::cout << "Triplet exists: ";
				std::cout << "{" << nums[i] << ", " << nums[j] << ", " << findnum << "}\n";
				i = nums.size();
				break;
			}
		}
	}
}

int Partition(std::vector<int>& nums, int start, int end)
{
	// Pick the rightmost element as a pivot from the array
	int pivot = nums[end];

	// elements less than the pivot will be pushed to the left of `pIndex`
	// elements more than the pivot will be pushed to the right of `pIndex`
	// equal elements can go either way
	int pIndex = start;

	// each time we find an element less than or equal to the pivot, `pIndex`
	// is incremented, and that element would be placed before the pivot.
	for (int i = start; i < end; i++)
	{
		if (nums[i] <= pivot)
		{
			int temp = nums[i];
			nums[i] = nums[pIndex];
			nums[pIndex] = temp;
			pIndex++;
		}
	}

	// swap `pIndex` with pivot
	int temp = nums[pIndex];
	nums[pIndex] = nums[end];
	nums[end] = temp;

	// return `pIndex` (index of the pivot element)
	return pIndex;
}

void Quicksort(std::vector<int>& nums, int start, int end)
{
	// base condition
	if (start >= end) {
		return;
	}

	// rearrange elements across pivot
	int pivot = Partition(nums, start, end);

	// recur on subarray containing elements that are less than the pivot
	Quicksort(nums, start, pivot - 1);

	// recur on subarray containing elements that are more than the pivot
	Quicksort(nums, pivot + 1, end);
}

int PowerOf2Higher(int number)
{
	int count = 0;
	float fnumber = number;

	while (fnumber > 1)
	{
		fnumber /= 2;
		count++;
	}

	return pow(2,std::max(count,1));

	/* Alternative method
	   number = number - 1;
 
      // do till only one bit is left
      while (number & number - 1) {
        number = number & number - 1;        // unset rightmost bit
      }
	  return number << 1;
	*/
}

int PowerOf2Lower(int number)
{
	int count = 0;
	float fnumber = number;

	while (fnumber > 1)
	{
		fnumber /= 2;
		if (fnumber >= 1)
		{
			count++;
		}
	}

	return pow(2, count);

  /* Alternative method
    number = number - 1;

    // do till only one bit is left
    while (number & number - 1) {
	  number = number & number - 1;        // unset rightmost bit
    }

    return number << 1;
  */
}

bool TupleFrequencySort(std::tuple<int, int, int>& t1, std::tuple<int, int, int>& t2)
{
	if (std::get<1>(t1) != std::get<1>(t2))
	{
		return std::get<1>(t1) > std::get<1>(t2);
	}
	else
	{
		return std::get<2>(t1) < std::get<2>(t2);
	}
}

void FrequencySort(std::vector <int> &numbers)
{
	std::unordered_map<int, std::pair<int, int>> CountMap;

	for (int i = 0; i < numbers.size(); i++)
	{
		if (CountMap.find(numbers[i]) != CountMap.end())
		{
			CountMap[numbers[i]].first++;
		}
		else
		{
			std::pair<int, int> tmp = std::pair<int, int>(1,i);
			CountMap[numbers[i]] = tmp;
		}
	}

	std::vector<std::tuple<int, int, int>> TupleNumList;
	std::unordered_map<int, std::pair<int, int>>::iterator mapit;

	for (mapit = CountMap.begin(); mapit != CountMap.end(); ++mapit)
	{
		TupleNumList.push_back(std::tuple<int, int, int>(mapit->first, mapit->second.first, mapit->second.second));
	}

	std::sort(TupleNumList.begin(), TupleNumList.end(), TupleFrequencySort);

	numbers.clear();
	for (int i = 0; i < TupleNumList.size(); i++)
	{
		numbers.insert(numbers.end(), std::get<1>(TupleNumList[i]), std::get<0>(TupleNumList[i]));
	}
}

bool LargestNumberSort(int n1, int n2)
{
	std::string n1st = std::to_string(n1);
	std::string n2st = std::to_string(n2);
	return n1st + n2st > n2st + n1st;
}

std::vector<std::vector<int>> FindAllDistinctCombos(std::vector<int> nums, int k)
{
	std::vector<std::vector<int>> AllCombos;
	std::vector<int> NewCombo(k);
	std::vector<int> elementshit(k);

	if (nums.size() < k)
	{
		return std::vector<std::vector<int>>();
	}

	std::sort(nums.begin(), nums.end());

	for (int x = 0; x < nums.size(); x++)
	{
		if (x + 1 < nums.size() && nums[x + 1] == nums[x])
		{
			continue;
		}

		NewCombo = std::vector<int>(k, nums[x]);
		elementshit = std::vector<int>(k, x);
		do
		{
			if (NewCombo[k - 1] != -1)
			{
				AllCombos.push_back(NewCombo);
				NewCombo[k - 1] = CycleElements(nums, elementshit[k - 1], k);

				if (NewCombo[k - 1] == -1)
				{
					int PrevE = k - 2;
					elementshit[k - 1] = elementshit[PrevE];
					while (elementshit[PrevE] >= x && PrevE > 0)
					{
						NewCombo[PrevE] = CycleElements(nums, elementshit[PrevE], k);
						if (NewCombo[PrevE] != -1)
						{
							for (int r = PrevE + 1; r < elementshit.size(); r++)
							{
								elementshit[r] = elementshit[PrevE];
								NewCombo[r] = NewCombo[PrevE];
							}
							break;
						}
						PrevE--;
					}
				}
			}
		} while (NewCombo[k-1] != -1 && elementshit[0] <= k);
	}

	return AllCombos;
}

int CycleElements(std::vector<int> array, int& elhit, int k)
{
	bool FoundNewNum = false;
	for (int i = elhit + 1; i < array.size() && i < elhit + k; i++)
	{
		if (array[i-1] != array[i])
		{
			elhit = i;
			FoundNewNum = true;
			break;
		}
	}

	if (!FoundNewNum)
	{
		return -1;
	}
	else
	{
		return array[elhit];
	}


}

// Backtracking algorithm example
std::vector<std::vector<int>> GetAllAddedCombos(int number)
{
	std::vector<std::vector<int>> Combinations;
	std::vector<int> curCombo;
	int startingNum = number;

	AddedCombosSolve(curCombo, startingNum, startingNum, Combinations);
	
    return Combinations;
}

void AddedCombosSolve(std::vector<int>& curNums, int num, int current, std::vector<std::vector<int>> &allCombos)
{
	if (current <= 0)
	{
		if (current == 0) { allCombos.push_back(curNums); }
		return;
	}

	for (int i = num; i > 0; i--)
	{
		curNums.push_back(i);
		AddedCombosSolve(curNums, std::min(i, current - i), current - i, allCombos);
		curNums.pop_back();
	}

}
// End

std::vector<std::vector<int>> GetAllTripToSum(std::vector<int> nums, int target)
{
	std::vector<std::vector<int>> Combinations;
	std::vector<int> curTrip;
	int remaining = target;

	if (nums.size() < 3)
	{
		return Combinations;
	}

	// Sort first to cut the computation time
	std::sort(nums.begin(), nums.end());

	TripleSum(nums, curTrip, target, 0, Combinations);

	return Combinations;
}

void TripleSum(std::vector<int> numbers, std::vector<int>& curTrip, int& remaining, int curIndex, std::vector<std::vector<int>>& allCombos)
{
	if (remaining >= 0 && curTrip.size() == 3)
	{
		allCombos.push_back(curTrip);
		return;
	}

	for (int i = curIndex; i < numbers.size(); )
	{
		if (numbers[i] > remaining)
		{
			break;
		}
		curTrip.push_back(numbers[i]);
		remaining -= numbers[i];
		TripleSum(numbers, curTrip, remaining, ++i, allCombos);
		remaining += curTrip[curTrip.size() - 1];
		curTrip.pop_back();
	}

}

void TraverseOrderTree(node<int>* Root)
{
	std::stack<node<int>*> NodeStack;
	node<int>* Current = Root;

	if (!Root)
	{
		return;
	}

	while (!NodeStack.empty() || Current != NULL)
	{
		if (Current != NULL)
		{
			NodeStack.push(Current);
			Current = Current->Left;
		}
		else
		{
			Current = NodeStack.top();
			NodeStack.pop();
			Current->printValue();
			Current = Current->Right;
		}
	}
}

void TraversePreOrderTree(node<int>* Root)
{
	std::stack<node<int>*> NodeStack;
	node<int>* Current = Root;

	if (!Root)
	{
		return;
	}

	while (!NodeStack.empty() || Current != NULL)
	{
		if (Current)
		{
			Current->printValue();
			if (Current->Right)
			{
				NodeStack.push(Current->Right);
			}
			Current = Current->Left;
		}
		else
		{
			Current = NodeStack.top();
			NodeStack.pop();
		}
	}
}

void TraversePostOrderTree(node<int>* Root)
{
	std::stack<node<int>*> NodeStack;
	std::stack<int> out;
	node<int>* Current = Root;
	NodeStack.push(Root);

	if (!Root)
	{
		return;
	}

	while (!NodeStack.empty())
	{
		// pop a node from the stack and push the data into the output stack
		node<int>* curr = NodeStack.top();
		NodeStack.pop();

		out.push(curr->getValue());

		// push the left and right child of the popped node into the stack
		if (curr->Left) {
			NodeStack.push(curr->Left);
		}

		if (curr->Right) {
			NodeStack.push(curr->Right);
		}
	}

	// print postorder traversal
	while (!out.empty())
	{
		std::cout << out.top() << " ";
		out.pop();
	}
}

bool TreeCousinCheck(node<int>* Root, node<int>* N1, node<int>* N2)
{
	int n1_depth = 0, n2_depth = 0;

	if (!N1 || !N2)
	{
		std::cout << "one of the node provided is not valid\n";
		return false;
	}

	if (!FindNodeDepth(Root, N1, 0, n1_depth))
	{
		std::cout << "Cant find node 2 in tree\n";
	}
	if (!FindNodeDepth(Root, N2, 0, n2_depth))
	{
		std::cout << "Cant find node 1 in tree\n";
	}

	if (n1_depth == n2_depth)
	{
		return true;
	}

	return false;
}

bool FindNodeDepth(node<int>* Root, node<int>* Node, int Depth, int& FoundDepth)
{
	if (Root == Node)
	{
		return true;
	}
	int currentDepth = Depth + 1;

	if ((Root->Left && FindNodeDepth(Root->Left, Node, Depth + 1, FoundDepth)) ||
		(Root->Right && FindNodeDepth(Root->Right, Node, Depth + 1, FoundDepth)))
	{
		FoundDepth = currentDepth;
	}
	
	return false;
}

bool CheckIfSumTree(node<int>* Root)
{
	int lSum = 0, rSum = 0;

	if (Root == NULL)
	{
		return false;
	}
	else if (!Root->Left && !Root->Right && Root->getValue() == 0)
	{
		return true;
	}

	if (Root->Left)
	{
		lSum = SumNodes(Root->Left);
	}
	if (Root->Right)
	{
		rSum = SumNodes(Root->Right);
	}

	if (lSum + rSum == Root->getValue())
	{
		return true;
	}

	return false;
}

int SumNodes(node<int>* Node)
{
	int sum = 0;

	if (!Node->Left && !Node->Right)
	{
		return Node->getValue();
	}

	if (Node->Left)
	{
		sum += SumNodes(Node->Left);
	}

	if (Node->Right)
	{
		sum += SumNodes(Node->Right);
	}

	if (sum != Node->getValue())
	{
		return -1;
	}

	return sum + Node->getValue();
}

int GetTreeDimention(node<int>* Root)
{
	int dimention = 0;

	if (!Root || (!Root->Left && !Root->Right) ) { return 0; }

	if (!Root->Left && Root->Right)
	{
		dimention = GetTreeDimention(Root->Right);
	}
	else if (Root->Left && !Root->Right)
	{
		dimention = GetTreeDimention(Root->Left);
	}
	else
	{
		dimention += CountPath(Root->Left);
		dimention += CountPath(Root->Right);
		dimention += 1;
	}

	return dimention;
}

int CountPath(node<int>* Node)
{
	if (!Node) { return 0; }

    int leftCount, rightCount;

	leftCount = CountPath(Node->Left);
	rightCount = CountPath(Node->Right);

	return std::max(leftCount, rightCount) + 1;
}

std::pair<int, int> closestPair(std::vector<int> n1, std::vector<int> n2, int target)
{
	int ClosestMatch = INT_MAX;
	std::pair<int, int> solutionPair = {-1, -1};

	if (n1.size() == 0 || n2.size() == 0)
	{
		return solutionPair;
	}

	int Index1 = 0, Index2 = n2.size() - 1;
	
	while (Index1 < n1.size() && Index2 > -1)
	{
		if (std::abs(target - (n1[Index1] + n2[Index2])) <= ClosestMatch)
		{
			solutionPair = { n1[Index1], n2[Index2] };
			ClosestMatch = std::abs(target - (n1[Index1] + n2[Index2]));
		}

		if (n1[Index1] + n2[Index2] > target)
		{
			Index2--;
		}
		else if(n1[Index1] + n2[Index2] < target)
		{
			Index1++;
		}
		else
		{
			Index1++;
			Index2--;
		}
	}

	return solutionPair;
}

std::vector <int> AltPosNeg(std::vector<int> numbers)
{
	int min = 0, minpos;
	int midpoint = 0;
	std::vector<int> posNegSort;

	std::sort(numbers.begin(), numbers.end());

	while (numbers[midpoint] < 0 && midpoint > -1)
	{ 
		midpoint++;
	}

	if (midpoint == numbers.size())
	{
		std::cout << "No negative numbers present";
		return numbers;
	}
	minpos = midpoint;

	while (min <= midpoint && minpos < numbers.size())
	{
		posNegSort.push_back(numbers[min++]);
		posNegSort.push_back(numbers[minpos++]);
	}

	while (min < midpoint)
	{
		posNegSort.push_back(numbers[min++]);
	}
	while (minpos < numbers.size())
	{
		posNegSort.push_back(numbers[minpos++]);
	}

	return posNegSort;
}

void ShuffleInPlace(std::vector<int>& nums, std::vector<int> pos)
{
	for (int i = 0; i < nums.size(); i++)
	{
		while (pos[i] != i)
		{
			int temp = nums[pos[i]];
			nums[pos[i]] = nums[i];
			nums[i] = temp;

			temp = pos[pos[i]];
			pos[pos[i]] = pos[i];
			pos[i] = temp;
		}
	}

}

void FindSymPairs(std::vector<std::pair<int, int>> pairs)
{
	std::set<std::pair<int, int>> pairSet;
	bool bFoundPair = false;
	for (int i = 0; i < pairs.size(); i++)
	{
		if ( pairSet.find(std::pair<int, int>(pairs[i].second, pairs[i].first)) != pairSet.end() )
		{
			std::cout << "{" << pairs[i].first << "," << pairs[i].second << "}" << " | " <<
				"{" << pairs[i].second << "," << pairs[i].first << "}" << std::endl;
			bFoundPair = true;
		}
		else
		{
			pairSet.insert(pairs[i]);
		}
	}

	if (!bFoundPair)
	{
		std::cout << "No pairs mirror each other";
	}

}

void FindNoneOverlappingPairs(std::vector<int> numbers)
{
	std::map<int, std::pair<int, int>> pairMap;
	bool bFoundPair = false;

	for (int i = 0; i < numbers.size() && !bFoundPair; i++)
	{
		for (int j = i + 1; j < numbers.size() && !bFoundPair; j++)
		{
			int sum = numbers[i] + numbers[j];
			if (pairMap.find(sum) != pairMap.end())
			{
				if ((i < pairMap[sum].first && j < pairMap[sum].first) ||
					(i > pairMap[sum].second && j > pairMap[sum].second))
				{
					std::cout << "(" << numbers[i] << "," << numbers[j] << ")";
					std::cout << " and ";
					std::cout << "(" << numbers[pairMap[sum].first] << "," << numbers[pairMap[sum].second] << ")\n";
					bFoundPair = true;
				}
			}
			else
			{
				pairMap[sum] = std::pair<int, int>{ i,j };
			}
		}
	}

	if (!bFoundPair)
	{
		std::cout << "No non-overlapping pairs is present in the array\n";
	}
}

void LargestSumBetweenVectors(std::vector<int> v1, std::vector<int> v2)
{
	int v1Index = v1.size()-1, v2Index = v2.size()-1;
	int TotalSum=0, v1Sum=0, v2Sum=0;

	std::set<int> v1Path, v2Path, FinalPath;

	while (v1Index >= 0 && v2Index >= 0)
	{
		if (v1[v1Index] == v2[v2Index])
		{
			if (v1Sum > v2Sum)
			{
				FinalPath.insert(v1Path.begin(), v1Path.end());
				TotalSum += v1Sum;
			}
			else
			{
				FinalPath.insert(v2Path.begin(), v2Path.end());
				TotalSum += v2Sum;
			}
			TotalSum += v1[v1Index];
			FinalPath.insert(v1[v1Index]);

			v1Path.clear();
			v2Path.clear();

			v1Sum = v2Sum = 0;
			v1Index--;
			v2Index--;
		}
		else if (v1[v1Index] > v2[v2Index])
		{
			v1Sum += v1[v1Index];
			v1Path.insert(v1[v1Index]);
			v1Index--;
		}
		else
		{
			v2Sum += v2[v2Index];
			v2Path.insert(v2[v2Index]);
			v2Index--;
		}
	}

	while (v1Index >= 0)
	{
		TotalSum += v1[v1Index];
		FinalPath.insert(v1[v1Index]);
		v1Index--;
	}

	while (v2Index >= 0)
	{
		TotalSum += v2[v2Index];
		FinalPath.insert(v2[v2Index]);
		v2Index--;
	}

	std::cout << "The max sum is "<< TotalSum << std::endl;
}

void SortByOccurence(std::vector<int> &numbers)
{
	std::unordered_map<int, int> hits;

	for (int i = 0; i < numbers.size(); i++)
	{
		if (hits.find(numbers[i]) != hits.end())
		{
			hits[numbers[i]]++;
		}
		else
		{
			hits[numbers[i]] = 1;
		}
	}

	numbers.clear();
	for (auto& hash : hits)
	{
		numbers.insert(numbers.end(), hash.second, hash.first);
	}

}

bool ConsecutiveInts(std::vector<int> numbers, int& min, int& max)
{
	std::set<int> orderedNums;

	for (int i = 0; i < numbers.size(); i++)
	{
		if (orderedNums.find(numbers[i]) != orderedNums.end())
		{
			return false;
		}
		orderedNums.insert(numbers[i]);
	}

	int lastseen = min = *orderedNums.begin();
	max = *orderedNums.rbegin();
	auto iterator = orderedNums.begin();

	for (int i = 1; i < orderedNums.size(); i++)
	{
		iterator++;
		if (lastseen + 1 != *iterator)
		{
			return false;
		}
		lastseen = *iterator;
	}


	return true;
}

void DecodeArray(std::vector<int> numbers)
{
	int m = numbers.size();
	// base case
	if (m == 0 || m == 2) {
		return;
	}

	// calculate the size of the original array
	int n = (sqrt(8 * m + 1) + 1) / 2;

	std::vector<int> A;

	// calculate the first element of the original array
	if (n == 1 || m == 1) {
		A.push_back(numbers[0]);
	}
	else if (n == 2) {
		A.push_back(numbers[0] - numbers[1]);
	}
	else {
		A.push_back((numbers[0] + numbers[1] - numbers[n - 1]) / 2);
	}

	// calculate the remaining elements of the original array using
	// the first element
	for (int i = 1; i < n; i++) {
		A.push_back(numbers[i - 1] - A[0]);
	}

	// print the original array
	for (int i = 0; i < n; i++) {
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
}

void CountDistinctAbsolutes(std::vector<int> numbers)
{
	std::set<int> DistinctAbsolutes;
	
	if (numbers.size() == 0) { return; }

	for (int i = 0; i < numbers.size(); i++)
	{
		DistinctAbsolutes.insert(abs(numbers[i]));
		while (i + 1 < numbers.size() && abs(numbers[i+1]) == numbers[i])
		{ 
			i++;
		}
	}

	std::cout << "The total number of distinct absolute values is " << DistinctAbsolutes.size() << " ( ";
	for (auto num : DistinctAbsolutes)
	{
		std::cout << num << " ";
	}
	std::cout << ")\n";

}

void CountDistinctAbsolutesNoSet(std::vector<int> numbers)
{
	int DistinctCount = 1;
	int Min = 0;
	int Max = 1;

	if (numbers.size() < 1)
	{
		return;
	}

	while (Min < Max)
	{
		while (Max < numbers.size() && numbers[Min] == numbers[Max])
		{
			Max++;
		}

		if (Max >= numbers.size())
		{
			break;
		}

		if (numbers[Max] > 0 && numbers[Min] < 0)
		{
			while (-abs(numbers[Max]) > numbers[Min])
			{
				Min++;
			}
		}

		if (abs(numbers[Min]) != abs(numbers[Max]))
		{
			DistinctCount++;
		}
		else
		{
			if (numbers[Min] < 0 && Max != numbers.size())
			{
				while (abs(numbers[Min]) >= numbers[Max] && Min > 0)
				{
					Min--;
				}
			}
		}

		Max++;
	}

	std::cout << "The total number of distinct absolute values is " << DistinctCount << "\n";
}

bool IndexOverlapCheck(std::pair<int, int> p1, std::pair<int, int> p2)
{
	if (p1.first == p2.first || p1.first == p2.second)
	{
		return false;
	}
	if (p1.second == p2.first || p1.second == p2.second)
	{
		return false;
	}

	return true;
}

void FourSumProblem(std::vector<int> numbers, int target)
{
	std::unordered_map<int, std::pair<int, int>> pairMatch;

	std::vector<std::set<int>> QuadSets;

	for (int i = 0; i < numbers.size(); i++)
	{
		for (int j = i+1; j < numbers.size(); j++)
		{
			int addition = numbers[i] + numbers[j];
			if (pairMatch.find(target - addition) != pairMatch.end())
			{
				std::pair<int, int> FoundPair = pairMatch[target - addition];
				std::set<int> temp = { i, j, FoundPair.first, FoundPair.second };
				if (IndexOverlapCheck(std::pair<int, int>(i, j), FoundPair))
				{
					bool bDup = false;
					for (auto set : QuadSets)
					{
						if (temp == set)
						{
							bDup = true;
							break;
						}
					}
					if (!bDup)
					{
						std::cout << "Quadruplet exists\n";
						QuadSets.push_back(std::set<int>{i, j,
							FoundPair.first, FoundPair.second});
					}
				}
			}
			pairMatch[addition] = std::pair<int, int>(i, j);
		}
	}

	if (QuadSets.size() > 0)
	{
		std::cout << "The following Quadruplet that give the sum of " << target << "were found:\n";
		for (int i = 0; i < QuadSets.size(); i++)
		{
			std::cout << "(";
			for (auto si : QuadSets[i])
			{
				std::cout << numbers[si] << " ";
			}
			std::cout << ")\n";
		}
	}
}

enum FacingDir
{
	North = 0,
	East = 1,
	West = -1,
	South = -2
};

bool IsMovesCirclar(std::string moves)
{
	std::pair<int, int> xyCoOrd = { 0,0 };
	FacingDir Dir = FacingDir::North;

	for (int i = 0; i < moves.size(); i++)
	{
		if (moves[i] == 'M')
		{
			switch (Dir)
			{
			case North:
				xyCoOrd.second++;
				break;
			case East:
				xyCoOrd.first++;
				break;
			case West:
				xyCoOrd.first--;
				break;
			case South:
				xyCoOrd.second--;
				break;
			default:
				break;
			}
	    }
		else
		{
			int DirNum = (int)Dir;
			if (moves[i] == 'L')
			{
				DirNum--;
			}
			else if(moves[i] == 'R')
			{
				DirNum++;
			}

			if (DirNum > 1) { DirNum = -2; }
			else if (DirNum < -2) { DirNum = 1; }

			Dir = (FacingDir)DirNum;
		}
	}

	if (xyCoOrd == std::pair<int, int>{0, 0})
	{
		return true;
	}

	return false;
}

void FindMinRemovals(std::vector<int> numbers)
{
	int left = 0, right = 0;
	int minNumber = INT_MAX, maxNumber = -INT_MAX;
	int maxNumberIndex = 0, minNumberIndex = 0;
	int removals = -1;
	int MinRemovals = INT_MAX;

	if (numbers.size() < 2)
	{
		std::cout << "List is not valid\n";
		return;
	}

	while (right < numbers.size())
	{
		minNumber = std::min(minNumber, numbers[right]);
		maxNumber = std::max(maxNumber, numbers[right]);
		removals = numbers.size() - (right - left) - 1;
		
		if (numbers[right] > numbers[maxNumberIndex])
		{
			maxNumberIndex = right;
		}
		if (minNumber == numbers[right])
		{
			minNumberIndex = right;
		}

		if (minNumber * 2 > maxNumber)
		{
			if (left != right)
			{
				MinRemovals = std::min(removals, MinRemovals);
			}
		}
		else
		{
			if (minNumberIndex > maxNumberIndex)
			{
				left = right = minNumberIndex;
			}
			else
			{
				while (left <= minNumberIndex)
				{
					left++;
				}
				minNumber = std::min(numbers[left], numbers[right]);
			}
		}

		right++;
	}

	if (MinRemovals != INT_MAX)
	{
		std::cout << "The minimum number of removals is " << MinRemovals << "\n";
	}
}

bool IsIsomorphicString(std::string S1, std::string IS)
{
	std::unordered_map<char, char> IsoMap;

	if (S1.size() != IS.size())
	{
		return false;
	}

	for (int i = 0; i < S1.size(); i++)
	{
		if (IsoMap.find(S1[i]) != IsoMap.end())
		{
			if (IsoMap[S1[i]] != IS[i])
			{
				return false;
			}
		}
		else
		{
			IsoMap[S1[i]] = IS[i];
		}
	}

	return true;
}

void RemoveSpaces(std::string& s1)
{
	bool bHitSpace = false;
	int NextInsertIndex = 0;

	for (int i = 0; i < s1.size(); i++)
	{
		while (s1[i] == ' ' && NextInsertIndex == 0)
		{
			i++;
			bHitSpace = true;
		}

		if (s1[i] == ' ')
		{
			if (bHitSpace != true)
			{
				bHitSpace = true;
				s1[NextInsertIndex++] = s1[i];
			}
		}
		else if (ispunct(s1[i]))
		{
			if (bHitSpace == true)
			{
				--NextInsertIndex;
			}
			bHitSpace = false;
			s1[NextInsertIndex++] = s1[i];
		}
		else
		{
			s1[NextInsertIndex++] = s1[i];
			bHitSpace = false;
		}
	}
	s1.erase(s1.begin() + --NextInsertIndex, s1.end());
	std::cout << "New string: \"" << s1 << "\"\n";
}

void StringPatternMatch(std::vector<std::string> strings, std::string patternString)
{
	std::vector<std::string> MatchingStrings;
	std::unordered_map<char, char> patternMap;

	for (int i = 0; i < strings.size(); i++)
	{
		bool bIsPatternMatch = true;
		patternMap.clear();
		if (strings[i].size() != patternString.size())
		{
			continue;
		}

		for (int j = 0; j < patternString.size(); j++)
		{
			if (patternMap.find(patternString[j]) == patternMap.end())
			{
				patternMap[patternString[j]] = strings[i][j];
			}
			else
			{
				if (patternMap[patternString[j]] != strings[i][j])
				{
					bIsPatternMatch = false;
					break;
				}
			}
		}
		patternMap.clear();

		for (int j = 0; j < patternString.size(); j++)
		{
			if (patternMap.find(strings[i][j]) == patternMap.end())
			{
				patternMap[strings[i][j]] = patternString[j];
			}
			else
			{
				if (patternMap[strings[i][j]] != patternString[j])
				{
					bIsPatternMatch = false;
					break;
				}
			}
		}

		if (bIsPatternMatch)
		{
			MatchingStrings.push_back(strings[i]);
		}
	}

	std::cout << "[";
	for (int i = 0; i < MatchingStrings.size(); i++)
	{
		std::cout << MatchingStrings[i];
		if (i != MatchingStrings.size() - 1)
		{
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
}

void GroupAnagrams(std::vector<std::string> strings)
{
	std::set<std::set<std::string>> anagrams;

	std::vector<std::string> list(strings);
	for (std::string& s : list) {       
		sort(s.begin(), s.end());
	}

	std::unordered_multimap<std::string, int> map;
	for (int i = 0; i < strings.size(); i++) {
		map.insert(make_pair(list[i], i));
	}


	auto itr = map.begin();
	while (itr != map.end())
	{
		std::set<std::string> anagram;
		for (auto curr = itr; itr != map.end() && itr->first == curr->first; itr++) {
			anagram.insert(strings[itr->second]);
		}
		if (anagram.size() > 1) {
			anagrams.insert(anagram);
		}
	}

	for (std::set<std::string> anagram : anagrams)
	{
		for (std::string s : anagram)
		{
			std::cout << s << ' ';
		}
		std::cout << std::endl;
	}
}

void EditsToString(std::string current, std::string target)
{
	int edits = 0;
	int currI = 0;
	int currT = 0;

	if (current == target)
	{
		std::cout << "False: The total number of edits required is 0 (both strings are the same)\n";
		return;
	}

	for (currI = 0, currT = 0; currI < current.size() && currT < target.size(); currI++, currT++)
	{
		if (current[currI] != target[currT])
		{
			edits++;

			if (current.size() > target.size())
			{
				currT--;
			}
			else if (current.size() < target.size())
			{
				currI--;
			}
		}
	}

	if (edits == 1)
	{
		std::cout << "True: ";
	}
	else
	{
		std::cout << "False: ";
	}
	std::cout << "The total number of edits required is " << edits << std::endl;
}

// Expand in both directions of `low` and `high` to find
// maximum length palindrome
void expand(std::string str, int low, int high, int& max)
{
	int len = str.length();
	int leftsum = 0, rightsum = 0;

	while (low >= 0 && high < len)
	{
		// update sum of the left and right half
		leftsum += str[low] - '0';
		rightsum += str[high] - '0';

		// update the maximum length of palindrome if the sum of the left half
		// becomes the same as the right half
		if (leftsum == rightsum && (high - low + 1) > max) {
			max = high - low + 1;
		}

		// Expand in both directions
		low--, high++;
	}
}

// Function to find the maximum length of a substring with an equal
// sum of left and right half
int longestPalindrome(std::string str, int n)
{
	// stores the maximum length of a substring with an equal sum
	// of left and right half
	int max = 0;

	// an even length palindrome will have two middle points

	// consider every adjacent pair of digits as midpoints and
	// expand in both directions to find the maximum length palindrome
	for (int i = 0; i < n - 1; i++) {
		expand(str, i, i + 1, max);
	}

	return max;
}

void PrintZigZagString(std::string string, int k)
{
	int row = 0;
	int vIndex = 0;
	bool Increment = true;
	std::vector<std::string> strings(k);
	std::string newString = "";

	for (int i = 0; i < string.size(); i++)
	{
		strings[vIndex] += string[i];

		if (vIndex == (k-1) && Increment)
		{
			Increment = false;
		}
		if (vIndex == 0 && !Increment)
		{
			Increment = true;
		}

		if (Increment)
		{
			vIndex++;
		}
		else
		{
			vIndex--;
		}
	}

	for (int i = 0; i < k; i++)
	{
		newString += strings[i];
	}

	std::cout << newString << "\n";
}

void LongestSubString(std::string string)
{
	std::unordered_map<char,int> lettersMap;
	int maxLenght = 0;
	std::string LongestSubString = "";
	std::string temp;

	for (int i = 0; i < string.size(); i++)
	{
		if (lettersMap.find(string[i]) != lettersMap.end())
		{
			if (maxLenght < lettersMap.size())
			{
				maxLenght = lettersMap.size();
				LongestSubString = temp;
				i = lettersMap[string[i]] + 1;
				lettersMap.clear();
				temp = "";
			}
		}
		temp += string[i];
		lettersMap[string[i]]= i;
	}

	if (LongestSubString == "")
	{
		LongestSubString = string;
	}

	std::cout << "The longest substring with all distinct characters is " << LongestSubString << std::endl;

}

void PermutationStringOfSub(std::string string, std::string substring)
{
	int SubSize = substring.size();
	int Start = 0, End = SubSize;
	std::string cur;

	if (string.size() < substring.size())
	{
		return;
	}
	std::sort(substring.begin(), substring.end());

	while (Start + SubSize <= string.size())
	{
		cur = string.substr(Start, End);

		if (cur == substring)
		{
			std::cout << "Anagram '" << string.substr(Start, End) << "' Preset at index " << Start << std::endl;
		}
		else
		{
			std::sort(cur.begin(), cur.end());
			if (cur == substring)
			{
				std::cout << "Anagram '" << string.substr(Start, End) << "' Preset at index " << Start << std::endl;
			}
		}

		Start++;
	}

}

void PrintCombos(std::vector<std::vector<std::string>> Strings)
{
	std::vector<int> indexes(Strings.size());
	std::fill(indexes.begin(), indexes.end(), 0);
	int lastElement = indexes.size() - 1;

	if (Strings.size() == 0) { return; }

	while (indexes[0] < Strings[0].size())
	{
		for (int i = 0; i <= lastElement; i++)
		{
			std::cout << Strings[i][indexes[i]] << " ";
		}
		std::cout << "\n";

		indexes[lastElement]++;
		if (indexes[lastElement] == Strings[lastElement].size())
		{
			for (int i = lastElement; i > 0; i--)
			{
				if (indexes[i] >= Strings[i].size())
				{
					indexes[i] = 0;
					indexes[i - 1]++;
				}
			}
		}
	}
}

int BalanceInversionsNeeded(std::string Expression)
{
	int Open = 0;
	int Imbalence = 0;

	if(Expression.size() == 0 || Expression.size() % 2 != 0)
	{
		std::cout << "This Expression cannot be balanced\n";
		return -1;
	}

	for (int i = 0; i < Expression.size(); i++)
	{
		// if we find a "}" with no "open", it will always need to be swapped
		// so lets assume it to be an make our list "open"
		if (Open == 0 && Expression[i] == '}')
		{
			Imbalence++;
			Open++;
		}
		else if (Expression[i] == '}' && Open > 0)
		{
			Open--;
		}
		if (Expression[i] == '{')
		{
			Open++;
		}

	}

	Imbalence += (Open/2);

	std::cout << "Minimum number of inversions needed is " << Imbalence << "\n";

	return Imbalence;
}

void PrintBalenceBracketCombos(std::string current, int open, int n, int OpenUsed)
{
	if (n % 2 != 0)
	{
		// cant be done
		return;
	}

	if (current.size() == n && open == 0)
	{
		std::cout << current << std::endl;
		return;
	}

	if (OpenUsed != n / 2)
	{
		PrintBalenceBracketCombos(current + "(", open+1, n, OpenUsed+1);
	}

	if (open > 0)
	{
		PrintBalenceBracketCombos(current + ")", open-1, n, OpenUsed);
	}
}

//Only one Traversal allowed
void FindFirstNonRepeatChar(std::string string)
{
	std::unordered_map<char, std::pair<int, int>> CharCount;
	int minIndex = INT_MAX;
	char character = '\0';

	for (int i = 0; i < string.size(); i++)
	{
		if (CharCount.find(string[i]) != CharCount.end())
		{
			CharCount[string[i]].second++;
		}
		else
		{
			CharCount[string[i]] = std::pair<int, int>(i, 1);
		}
	}

	for (auto &letter : CharCount)
	{
		if (letter.second.second == 1 && letter.second.first < minIndex)
		{
			minIndex = letter.second.first;
			character = string[minIndex];
		}
	}

	if (character != '\0')
	{
		std::cout << "The first non-repeating character in the string is " << character << "\n";
	}
	else
	{
		std::cout << "No non-repeating character found \n";
	}
}

void FindLongestPal(std::string s)
{
	std::unordered_map<char, int> chars;
	std::string LongestPal = "", ReversePal = "";
	char pivot = '\0';

	if (s.size() < 2) 
	{
		return;
	}

	for (int i = 0; i < s.size(); i++)
	{
		if (chars.find(s[i]) != chars.end())
		{
			chars[s[i]]++;
		}
		else
		{
			chars[s[i]] = 1;
		}
	}

	for (auto& c : chars)
	{
		if (c.second == 1 )
		{
			if (pivot == '\0')
			{
				pivot = c.first;
			}
		}
		else 
		{
			if (c.second % 2 != 0 && pivot == '\0')
			{
				pivot = c.first;
			}
			int divtwo = std::ceil(c.second / 2);
			LongestPal += std::string((divtwo),c.first);
			ReversePal = std::string((divtwo), c.first) + ReversePal;
		}
	}

	LongestPal = LongestPal + pivot + ReversePal;

	std::cout << "The longest palindrome is " << LongestPal << "\n";
}

void PrintNonOverlapSubStrings(std::string s, int index, std::vector<std::vector<std::string>> &combinations, std::vector<std::string> current)
{
	if (index == s.size())
	{
		combinations.push_back(current);
		return;
	}

	current.push_back(std::string("") + s[index]);
	PrintNonOverlapSubStrings(s, index + 1, combinations, current);
	current.pop_back();

	if (current.size() == 0)
	{
		return;
	}

	current[current.size() - 1] += s[index];
	PrintNonOverlapSubStrings(s, index + 1, combinations, current);
}

void StringDiff(std::string X, std::string Y)
{

}

int KnapSackProblem(std::vector<int> value, std::vector<int> weight, int CurWeight, int curri, std::map <std::string, int> lookup)
{
	if (CurWeight < 0)
	{
		return INT_MIN;
	}

	if (curri == weight.size() || CurWeight == 0)
	{
		return 0;
	}

	std::string key = std::to_string(curri) + '|' + std::to_string(CurWeight);

	if (lookup.find(key) == lookup.end())
	{
		int IncludeSum = value[curri] + KnapSackProblem(value, weight, CurWeight - weight[curri], curri + 1, lookup);

		int ExcludeSum = KnapSackProblem(value, weight, CurWeight, curri + 1, lookup);

		lookup[key] = std::max(IncludeSum, ExcludeSum);
	}

	return lookup[key];
}

int RobCuttingProfit(std::vector<int> length, std::vector<int> price, int CurLen, int StartI)
{
	int MaxProfit = INT_MIN;

	if (CurLen == 0)
	{
		return 0;
	}

	for (int i = StartI; length[i] <= CurLen && i < length.size(); i++)
	{
		MaxProfit = std::max(MaxProfit, price[i] + RobCuttingProfit(length, price, CurLen - length[i], i));
	}

	return MaxProfit;
}

int EvaluateMathExpression(std::string Equation)
{
	int finishSum = 0, lastnum = 0;
	int multi = 1;
	std::stack<int> signStack;

	signStack.push(multi);

	for (int i = 0; i < Equation.size(); i++)
	{
		if (std::isdigit(Equation[i]))
		{
			lastnum = lastnum * 10 + (Equation[i] - '0');
		}
		else if (Equation[i] == '+')
		{
			finishSum += multi * lastnum;

			lastnum = 0;

			multi = signStack.top();
		}
		else if (Equation[i] == '-')
		{
			finishSum += multi * lastnum;

			lastnum = 0;

			multi = signStack.top() * -1;
		}
		else if (Equation[i] == '(')
		{
			signStack.push(multi);
		}
		else if (Equation[i] == ')')
		{
			signStack.pop();
		}
	}

	finishSum += multi * lastnum;
	return finishSum;
}

int MinCoinChange(std::vector<int> validCoins, int MoneyLeft)
{
	int MinCoinsNeeded = INT_MAX-1;

	if (MoneyLeft < 0)
	{
		return MinCoinsNeeded;
	}
	else if (MoneyLeft == 0)
	{
		return 0;
	}

	for (int i = 0; i < validCoins.size(); i++)
	{
		MinCoinsNeeded = std::min(MinCoinsNeeded, 1 + MinCoinChange(validCoins, MoneyLeft - validCoins[i]));
	}

	return MinCoinsNeeded;
}

int MinCoinChangeDynamic(std::vector<int> validCoins, int MoneyLeft)
{
	std::vector<int> T(MoneyLeft + 1);
	T[0] = 0;

	for (int i = 1; i <= MoneyLeft; i++)
	{
		// initialize the minimum number of coins needed to infinity
		T[i] = INT_MAX;
		int result = INT_MAX;

		// do for each coin
		for (int c : validCoins)
		{
			// check if the index doesn't become negative by including current coin `c`
			if (i - c >= 0) {
				result = T[i - c];
			}

			// if total can be reached by including current coin `c`,
			// update the minimum number of coins needed `T[i]`
			if (result != INT_MAX) {
				T[i] = std::min(T[i], result + 1);
			}
		}
	}

	// `T[target]` stores the minimum number of coins needed to get a total of `target`
	return T[MoneyLeft];
}

void ReverseWordOrder(std::string& words)
{
	std::stack<std::string> stackWords;
	std::string word;
	for (int i = 0; i < words.size(); i++)
	{
		if (words[i] == ' ')
		{
			stackWords.push(word);
			word = "\0";
		}
		else
		{
			word += words[i];
		}
	}

	stackWords.push(word);
	words = "\0";

	while (stackWords.size() > 0)
	{
		words += stackWords.top();
		if (stackWords.size() != 1)
		{
			words += " ";
		}
		stackWords.pop();
	}
}

bool StringMatchPattern(std::string word, std::string pattern)
{
	std::string matchingChars = "";

	for (int i = 0; i < word.size(); i++)
	{
		if (pattern.find(word[i]) != std::string::npos)
		{
			if (matchingChars.size() == 0 || matchingChars[matchingChars.size() - 1] != word[i])
			{
				matchingChars += word[i];
			}
		}
	}

	if (matchingChars != pattern)
	{
		return false;
	}

	return true;
}

void BinaryCombos(std::string original, std::vector<int> current, int index)
{
	if (current.size() == original.size())
	{
		for (int i = 0; i < current.size(); i++)
		{
			std::cout << current[i];
		}
		std::cout << std::endl;
		return;
	}

	if (original[index] != '?')
	{
		current.push_back(original[index] - '0');
		BinaryCombos(original, current, index +1);
	}
	else
	{
		current.push_back(0);
		BinaryCombos(original, current, index + 1);
		current.pop_back();

		current.push_back(1);
		BinaryCombos(original, current, index + 1);
	}
}

std::vector<int> FindPeakElements(std::vector<int> numbers)
{
	std::vector<int> PeakElements;
	BSACheckPeak(0, std::floor((numbers.size()-1) / 2), numbers.size()-1, numbers, PeakElements);
	return PeakElements;
}

void BSACheckPeak(int min, int mid, int max, std::vector<int> numbers, std::vector<int>& PeakNums)
{
	if (min == mid)
	{
		if (numbers[mid] > numbers[max] && min == 0)
		{
			PeakNums.push_back(numbers[mid]);
		}
		return;
	}
	else if (mid == max)
	{
		if (numbers[mid] > numbers[min] && max == numbers.size()-1)
		{
			PeakNums.push_back(numbers[mid]);
		}
		return;
	}

	if (numbers[mid] > numbers[mid + 1] && numbers[mid] > numbers[mid - 1])
	{
		PeakNums.push_back(numbers[mid]);
	}

	BSACheckPeak(min, std::floor((min + mid) / 2), mid, numbers, PeakNums);
	BSACheckPeak(mid, std::floor((mid + max) / 2) + 1, max, numbers, PeakNums);
}

int DACDFindMaxSum(std::vector<int> nums, int low, int high)
{
	int mid = (low + high) / 2;

	if (high <= low)
	{
		return nums[low];
	}

	int MaxLeft = INT_MIN;
	int sum = 0;
	// start from the middle and go back
	for (int i = mid; i >= low; i--)
	{
		sum += nums[i];
		if (sum > MaxLeft) 
		{
			MaxLeft = sum;
		}
	}

	int MaxRight = INT_MIN;
	sum = 0;
	// start from the middle and go forward
	for (int i = mid + 1; i <= high; i++)
	{
		sum += nums[i];
		if (sum > MaxRight)
		{
			MaxRight = sum;
		}
	}

	int max_combo = std::max(DACDFindMaxSum(nums, low, mid), DACDFindMaxSum(nums, mid + 1, high));

	return std::max(max_combo, MaxLeft + MaxRight);
}

int runMFunctions()
{
	//https://www.techiedelight.com/check-subarray-with-0-sum-exists-not/
	int Array[] = { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
	int ArraySize = sizeof(Array) / sizeof(int);
	if (DetectSubArrayZero(Array, ArraySize))
	{
		std::cout << "Array contians subarray which equals 0\n";
	}
	//End

	//https://www.techiedelight.com/find-maximum-length-sub-array-having-given-sum/
	std::vector<int> numbers = { 5, 6, -5, 5, 3, 5, 3, -2, 0 };
	int target = 8;
	std::vector<int> largetSubArray = LargestSubArrayToTarget(numbers, target);
	if (largetSubArray.size() == 0) { std::cout << "No subarray sum to target\n"; }
	else
	{
		std::cout << "Larget subarray to target is { ";
		for (auto i : largetSubArray) { std::cout << i << " "; }
		std::cout << "}. Length = " << largetSubArray.size() << std::endl;
	}
	//End

	//https://www.techiedelight.com/find-sub-array-with-0-sum/
	numbers = { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
	FindAllZeroSubArrays(numbers);
	//End

	//https://www.techiedelight.com/sort-array-containing-0s-1s-2s-dutch-national-flag-problem/
	numbers = { 0, 1, 2, 2, 1, 0, 0, 2, 0, 1, 1, 0 };
	Sort012Array(numbers);
	std::cout << "Sorted Array = { ";
	for (auto i : numbers) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	//End

	//https://www.techiedelight.com/inplace-merge-two-sorted-arrays/
	std::vector<int> Nums1 = { 1, 4, 7, 8, 10 };
	std::vector<int> Nums2 = { 2, 3, 9 };
	inPlaceTwoArrayMerge(Nums1, Nums2);
	std::cout << "inPlaceTwoArrayMerge:\nArray 1 = { ";
	for (auto i : Nums1) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	std::cout << "Array 2 = { ";
	for (auto i : Nums2) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	//End

	//https://www.techiedelight.com/merge-two-arrays-satisfying-given-constraints/
	Nums1 = { 0, 2, 0, 3, 0, 5, 6, 0, 0 };
	Nums2 = { 1, 8, 9, 10, 15 };
	inPlaceTwoArrayMergeConstraints(Nums1, Nums2);
	std::cout << "inPlaceTwoArrayMergeConstraints:\nArray 1 = { ";
	for (auto i : Nums1) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	std::cout << "Array 2 = { ";
	for (auto i : Nums2) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	//End

	//https://www.techiedelight.com/find-maximum-length-sub-array-equal-number-0s-1s/
	numbers = { 0, 0, 1, 0, 1, 0, 0 };
	largestSubarray01(numbers);
	//End

	//https://www.techiedelight.com/replace-element-array-product-every-element-without-using-division-operator/
	numbers = { 1, 2, 3, 4, 5 };
	ProductReplace(numbers);
	//End

	//https://www.techiedelight.com/find-largest-sub-array-formed-by-consecutive-integers/
	numbers = { 4,1,0,2 };
	largestsubarrayConInts(numbers);
	//End

	//https://www.techiedelight.com/find-maximum-difference-between-two-elements-array/
	numbers = { 3,2,10,1,3,5,1 };
	FindMaxDiff(numbers);
	//End

	//https://www.techiedelight.com/find-longest-bitonic-subarray-array/
	numbers = { 3, 5, 8, 4, 5, 9, 10, 8, 5, 3, 4 };
	LongestBitonicSubArray(numbers);
	//End

	//https://www.techiedelight.com/print-continuous-subarray-with-maximum-sum/
	numbers = { 8, -7, -3, 5, 6, -2, 3, -4, 2 };
	FindMaxContinuesSubArray(numbers);
	//End

	//https://www.techiedelight.com/find-maximum-sequence-of-continuous-1s-can-formed-replacing-k-zeroes-ones/
	numbers = { 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0 };
	int k = 3;
	MaxSequeceOnes(numbers, k);
	//End

	//https://www.techiedelight.com/find-distinct-combinations-of-given-length/
	numbers = { 1, 2, 1, 1 };
	k = 3;
	PrintAllCombos(numbers, k);
	//End

	//https://www.techiedelight.com/find-minimum-sum-subarray-given-size-k/
	numbers = { 10, 4, 2, 5, 6, 3, 8, 1 };
	k = 3;
	FindMinSubArrayOfSize(numbers, k);
	//End

	//https://www.techiedelight.com/find-subarray-having-given-sum-given-array
	numbers = { 0, 5, -7, 1, -4, 7, 6, 1, 4, 1, 10 };
	k = -3;
	FindSubArrayWithSum(numbers, k);
	//End

	//https://www.techiedelight.com/maximum-profit-earned-buying-and-selling-shares/
	numbers = { 10, 8, 6, 5, 4, 2 };
	MaxStockProfit(numbers);
	//End

	//https://www.techiedelight.com/minimum-number-of-platforms-needed-avoid-delay-arrival-train/
	std::vector<double> arrivals = { 2.00, 2.10 ,3.00, 3.20, 3.50, 5.00 };
	std::vector<double> departers = { 2.30, 3.40, 3.20, 4.30, 4.00, 5.20 };
	MaxPlatformsNeeded(arrivals, departers);
	//End

	//https://www.techiedelight.com/reverse-every-consecutive-m-elements-given-subarray/
	numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int startingIndex = 1, endingIndex = 7;
	int m = 3;
	SubArrayRevert(numbers, startingIndex, endingIndex, m);
	//End

	//https://www.techiedelight.com/find-sorted-triplet-array/
	numbers = { 5, 4, 3, 7, 6, 1, 9 };
	std::tuple<int, int, int> triplet(-1, -1, -1);
	triplet = FindSortedTriplet(numbers);
	if (std::get<0>(triplet) != -1)
	{
		std::cout << "Triplet found: ("
			<< std::get<0>(triplet) << ", "
			<< std::get<1>(triplet) << ", "
			<< std::get<2>(triplet) << ")\n";
	}
	else
	{
		std::cout << "Triplet not found\n";
	}
	//End

	//https://www.techiedelight.com/count-strictly-increasing-sub-arrays/
	numbers = { 1, 2, 4, 5, 6 };
	IncreasingSubArrays(numbers);
	//End

	//https://www.techiedelight.com/find-minimum-moves-required-converting-array/
	numbers = { 8, 9, 8 };
	FindMinMovesToZero(numbers);
	//End

	//https://www.techiedelight.com/find-pair-with-given-sum-circularly-sorted-array/
	numbers = { 10, 12, 15, 3, 6, 8, 9 };
	int sum = 18;
	FindPairForSumInCir(numbers, sum);
	//End

	//https://www.techiedelight.com/find-triplet-given-with-given-sum/
	numbers = { 2, 7, 4, 0, 9, 5, 1, 3 };
	sum = 6;
	FindTripletToSum(numbers, sum);
	//End

	//https://www.techiedelight.com/quicksort/
	numbers = { 10, 12, 15, 3, 6, 8, 9 };
	Quicksort(numbers, 0, numbers.size() - 1);
	std::cout << "Quicksorted Array = { ";
	for (auto i : numbers) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	//End

	//https://www.techiedelight.com/round-next-highest-power-2/
	std::cout << PowerOf2Higher(52) << "\n";
	//End

	//https://www.techiedelight.com/round-previous-power-2/
	std::cout << PowerOf2Lower(52) << "\n";
	//End

	//https://www.techiedelight.com/sort-elements-by-their-frequency-and-index/
	numbers = { 3, 3, 1, 1, 1, 8, 3, 6, 8, 7, 8 };
	FrequencySort(numbers);
	std::cout << "frequency and index sorted array = { ";
	for (auto i : numbers) { std::cout << i << " "; }
	std::cout << "}" << std::endl;
	//End

	//https://www.techiedelight.com/find-largest-number-possible-set-given-numbers/
	numbers = { 10, 68, 75, 7, 21, 12 };
	std::sort(numbers.begin(), numbers.end(), LargestNumberSort);
	std::string BiggestNum = "";
	for (auto i : numbers) { BiggestNum += std::to_string(i); }
	std::cout << "The biggest number we can make is " << BiggestNum << std::endl;
	//End

	//https://www.techiedelight.com/print-matrix-spiral-order/
	std::vector<float> fnums = { 1,2,3,4,5,16,17,18,19,6,15,24,25,20,7,14,23,22,21,8,13,12,11,10,9 };
	Martix M(5, 5, fnums);
	M.PrintSpiral();
	M.Reset();
	//End

	//https://www.techiedelight.com/create-spiral-matrix-given-array/
	fnums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	M.SpiralInsert(fnums, 5, 5);
	M.PrintMartix();
	M.Reset();
	//End

	//https://www.techiedelight.com/change-elements-row-column-j-matrix-0-cell-j-value-0/
	fnums = { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
	M = Martix(5, 5, fnums);
	M.ZeroChangeMartix();
	M.PrintMartix();
	M.Reset();
	//End


	//https://www.techiedelight.com/print-matrix-diagonally-positive-slope/
	fnums = { 1,2,3,4,5,2,3,4,5,6,3,4,5,6,7,4,5,6,7,8,5,6,7,8,9 };
	M = Martix(5, 5, fnums);
	M.PrintDiag();
	//End

	//https://www.techiedelight.com/find-common-elements-present-every-row-given-matrix/
	M = Martix(8, 6,
		{ { 7,1,3,5,3,6 },
		  { 2,3,6,1,1,6 },
		  { 6,1,7,2,1,4 },
		  { 6,6,7,1,3,3 },
		  { 5,5,6,1,5,4 },
		  { 3,5,6,2,7,1 },
		  { 4,1,4,3,6,4 },
		  { 4,6,1,7,4,3 } }
	);
	std::vector<float> commonRowNums = M.findRowCommon();
	std::cout << "The common elements are ";
	for (auto i : commonRowNums) { std::cout << i << " "; }
	std::cout << std::endl;
	//End

	//https://www.techiedelight.com/find-maximum-value-choices-indexes/
	M = Martix(5, 5,
		{ { 1,2,-1,-4,-20},
		  { -8,-3,4,2,1},
		  { 3,8,6,1,3},
		  { -4,-1,1, 7,-6},
		  { 0,-4,10,-5,1 } }
	);
	int Test = M.FindMaxValue();
	std::cout << "Max Value in Martix is " << Test << std::endl;
	//End

	//https://www.techiedelight.com/find-kth-smallest-value-sorted-matrix/
	M = Martix(3, 3, { {-3,1,3}, {-2,2,4},{1,3,5} });
	int num = M.FindNumAtSortedIndex(6);
	std::cout << "The index of sorted matrix [6] is " << num << std::endl;
	//End

	//https://www.techiedelight.com/find-distinct-combinations-given-length-repetition-allowed/
	std::vector<std::vector<int>> AllCombos = FindAllDistinctCombos({ 1,2,3,4 }, 4);
	for (int i = 0; i < AllCombos.size(); i++)
	{
		std::cout << "{ ";
		for (int j = 0; j < AllCombos[i].size(); j++)
		{
			std::cout << AllCombos[i][j] << " ";
		}
		std::cout << "}, ";
	}
	//End

	//https://www.techiedelight.com/print-all-combination-numbers-from-1-to-n/
	int number = 5;
	std::vector<std::vector<int>> CombosToNumber = GetAllAddedCombos(number);
	//End

	//https://www.techiedelight.com/print-triplets-array-sum-less-equal-given-number/
	numbers = { 2, 7, 4, 9, 5, 1, 3 };
	number = 10;
	std::vector<std::vector<int>> TripletsForNum = GetAllTripToSum(numbers, number);
	std::cout << std::endl;
	//End

	{
		//Create Tree
		node<int>* root = new node<int>(1);
		root->Left = new node<int>(2);
		root->Right = new node<int>(3);
		root->Left->Left = new node<int>(4);
		root->Right->Left = new node<int>(5);
		root->Right->Right = new node<int>(6);
		root->Right->Left->Left = new node<int>(7);
		root->Right->Left->Right = new node<int>(8);
		//End

		//https://www.techiedelight.com/inorder-tree-traversal-iterative-recursive/
		TraverseOrderTree(root);
		std::cout << std::endl;
		//End

		//https://www.techiedelight.com/preorder-tree-traversal-iterative-recursive/
		TraversePreOrderTree(root);
		std::cout << std::endl;
		//End

		//https://www.techiedelight.com/postorder-tree-traversal-iterative-recursive/
		TraversePostOrderTree(root);
		std::cout << std::endl;
		//End

		//https://www.techiedelight.com/determine-two-nodes-are-cousins/
		if (TreeCousinCheck(root, root->Left->Left, root->Right->Left->Left))
		{
			std::cout << "Nodes are cousins of each other\n";
		}
		else
		{
			std::cout << "Nodes are not cousins of each other\n";
		}
		//End

		node<int>* root2 = new node<int>(44);
		root2->Left = new node<int>(9);
		root2->Right = new node<int>(13);
		root2->Left->Left = new node<int>(4);
		root2->Left->Right = new node<int>(5);
		root2->Right->Left = new node<int>(6);
		root2->Right->Right = new node<int>(7);

	    //https://www.techiedelight.com/check-given-binary-tree-sum-tree-not/
		if (CheckIfSumTree(root2))
		{
			std::cout << "Binary tree is a sum tree\n";
		}
		else
		{
			std::cout << "Binary tree is not a sum tree\n";
		}
		//Clean up tree
		delete root2;
		//End

		root2 = new node<int>(1);

		root2->Left = new node<int>(2);
		root2->Left->Right = new node<int>(4);

		root2->Right = new node<int>(3);
		root2->Right->Left = new node<int>(5);
		root2->Right->Right = new node<int>(6);

		root2->Right->Left->Left = new node<int>(7);
		root2->Right->Left->Right = new node<int>(8);

		// https://www.techiedelight.com/find-diameter-of-a-binary-tree/
		std::cout << "The diameter  of the tree is " << GetTreeDimention(root2) << std::endl;
		delete root2;
		//End

		//Clean up tree
		delete root;
		//End
	}

	//https://www.techiedelight.com/find-closest-pair-two-sorted-arrays/
	Nums1 = { 1, 8, 10, 12 };
	Nums2 = { 2, 4, 9, 15 };
	target = 11;
	std::pair<int, int> cPair = closestPair(Nums1, Nums2, target);
	std::cout << "The closest pair is [" << cPair.first << ", " << cPair.second << "]" << std::endl;
	//End

	//https://www.techiedelight.com/rearrange-array-positive-negative-numbers-alternate-positions/
	numbers = { 9, -3, 5, -2, 8, 6, 1, 3 };
	numbers = AltPosNeg(numbers);
	//End

	//https://www.techiedelight.com/shuffle-array-according-to-given-order
	numbers = { 1, 2, 3, 4, 5 };
	std::vector<int> positions = { 3, 2, 4, 1, 0 };
	ShuffleInPlace(numbers, positions);
	//End

	//https://www.techiedelight.com/find-symmetric-pairs-array-pairs/
	std::vector<std::pair<int, int>> pairs = { {3,4}, {1,2}, {5,2}, {7,10}, {4,3}, {2,5} };
	FindSymPairs(pairs);
	//End

	//https://www.techiedelight.com/find-two-non-overlapping-pairs-sum-array/
	numbers = { 3, 4, 7, 4 };
	FindNoneOverlappingPairs(numbers);
	//End

	//https://www.techiedelight.com/find-maximum-sum-path-involving-elements-given-arrays/
	Nums1 = { 3, 6, 7, 8, 10, 12, 15, 18, 100 };
	Nums2 = { 1, 2, 3, 5, 7, 9, 10, 11, 15, 16, 18, 25, 50 };
	LargestSumBetweenVectors(Nums1, Nums2);
	//End

	//https://www.techiedelight.com/group-elements-array-based-first-occurrence/
	numbers = { 5, 4, 5, 5, 3, 1, 2, 2, 4 };
	SortByOccurence(numbers);
	//End

	//https://www.techiedelight.com/check-array-formed-consecutive-integers/
	numbers = { 4, 2, 4, 3, 1 };
	int min, max;
	if (ConsecutiveInts(numbers, min, max))
	{
		std::cout << "The array contains consecutive integers from " << min << " to " << max << std::endl;
	}
	else
	{
		std::cout << "The array does not contain consecutive integers." << std::endl;
	}
	//End

	//https://www.techiedelight.com/decode-the-array-constructed-another-array/
	numbers = { 3,8,7 };
	DecodeArray(numbers);
	//End

	//https://www.techiedelight.com/count-distinct-absolute-values-sorted-array
	numbers = { -3, -1, 0, 1, 1, 3, 5, 7 };
	CountDistinctAbsolutes(numbers);
	//Now do this again without extra space
	CountDistinctAbsolutesNoSet(numbers);
	//End

	//https://www.techiedelight.com/4-sum-problem/
	numbers = { 2, 7, 4, 0, 9, 5, 1, 3 };
	target = 20;
	FourSumProblem(numbers, target);
	//End

	//https://www.techiedelight.com/check-given-set-moves-circular-not/
	std::string Moves = "MRMLMRMRMMRMM";
	if (IsMovesCirclar(Moves))
	{
		std::cout << "Set of moves \"" << Moves << "\" is circular\n";
	}
	else
	{
		std::cout << "Set of moves \"" << Moves << "\" is not circular\n";
	}
	//End

	//https://www.techiedelight.com/find-minimum-removals-required-array/
	numbers = { 4, 6, 1, 7, 5, 9, 2 };
	FindMinRemovals(numbers);
	//End

	//https://www.techiedelight.com/isomorphic-strings/
	std::string S1 = "ACAB";
	std::string IS = "XCXY";
	bool bIsIsomString = IsIsomorphicString(S1, IS);
	if (bIsIsomString)
	{
		std::cout << "String S1 is an Isomorphic Strings\n";
	}
	//End

	//https://www.techiedelight.com/remove-extra-spaces-string/
	S1 = " Hello .   This is   a C++   program !! ";
	std::cout << "Old string: \"" << S1 << "\"\n";
	RemoveSpaces(S1);
	//End

	//https://www.techiedelight.com/find-words-that-follows-given-pattern/
	std::vector<std::string> strings = { "otto", "leet", "abcd", "loot", "geek", "cool", "for", "peer", "dear", "seed", "meet", "noon", "mess", "loss" };
	std::string patternString = "pqrs";
	StringPatternMatch(strings, patternString);
	//End

	//https://www.techiedelight.com/group-anagrams-together-given-list-words/
	strings = { "CARS", "REPAID", "DUES", "NOSE", "SIGNED", "LANE", "PAIRED", "ARCS", "GRAB", "USED", "ONES", "BRAG", "SUED", "LEAN", "SCAR", "DESIGN" };
	GroupAnagrams(strings);
	//End

	//https://www.techiedelight.com/determine-string-transformed-into-another-string-single-edit/
	EditsToString("xyz", "xyx");
	//End

	//https://www.techiedelight.com/longest-even-length-palidromic-sum-substring/
	std::cout << "The length of the longest palindromic sum substring is " << longestPalindrome("546374", 6) << "\n";
	//End

	//https://www.techiedelight.com/print-string-in-zig-zag-form-k-rows/
	PrintZigZagString("THISPROBLEMISAWESOME", 4);
	//End

	//https://www.techiedelight.com/find-longest-substring-given-string-containing-distinct-characters/
	LongestSubString("aaaaaa");
	//End

	//https://www.techiedelight.com/find-substrings-string-permutation-given-string/
	PermutationStringOfSub("XYYZXZYZXXYZ", "XYZ");
	//End

	//https://www.techiedelight.com/combinations-phrases-formed-picking-words-lists/
	std::vector<std::string> v1 = { "John", "Emma" };
	std::vector<std::string> v2 = { "Plays", "Hates", "Watches" };
	std::vector<std::string> v3 = { "Cricket", "Soccer", "Chess" };
	PrintCombos(std::vector<std::vector<std::string>>{v1, v2, v3});
	//End

	//https://www.techiedelight.com/minimum-number-inversions-expression-balanced/
	BalanceInversionsNeeded("}}}}}}");
	//End

	//https://www.techiedelight.com/find-first-non-repeating-character-string-one-traversal/
	FindFirstNonRepeatChar("ABCDBAGHC");
	//End

	//https://www.techiedelight.com/find-combinations-non-overlapping-substrings-string/
	std::vector<std::vector<std::string>> combinations;
	PrintNonOverlapSubStrings("ABCD", 0, combinations, std::vector<std::string>());
	//End

	//https://www.techiedelight.com/find-strings-given-length-containing-balanced-parentheses/
	PrintBalenceBracketCombos(std::string(), 0, 6, 0);
	//End

	//https://www.techiedelight.com/implement-diff-utility/
	StringDiff("XMJYAUZ", "XMJAATZ");
	//End

	//https://www.techiedelight.com/0-1-knapsack-problem/
	std::map <std::string, int> lookupMap;
	std::cout<< "Knapsack value is " << KnapSackProblem(std::vector<int>{20, 5, 10, 40, 15, 25 }, std::vector<int>{1, 2, 3, 8, 7, 4}, 10, 0, lookupMap) << "\n";
	//End

	//https://www.techiedelight.com/rod-cutting/
	std::cout << "Max Profit on lenght of rod is: " << 
		RobCuttingProfit({ 1, 2, 3, 4, 5, 6, 7, 8 }, { 1, 5, 8, 9, 10, 17, 17, 20 }, 4, 0) << "\n";
	//End

	//https://www.techiedelight.com/evaluate-given-expression/
	std::cout<< EvaluateMathExpression("10 - (5 + 4)") << "\n";
	//End

	//https://www.techiedelight.com/construct-longest-palindrome-string/
	FindLongestPal("ABCDD");
	//End

	//https://www.techiedelight.com/coin-change-making-problem-unlimited-supply-coins/
	std::cout<<"The minimum number of coins required to get the desired change is "
		<< MinCoinChange(std::vector<int>{1, 3, 5, 7}, 18) << "\n";
	std::cout << "The minimum number of coins required to get the desired change is "
		<< MinCoinChangeDynamic(std::vector<int>{1, 3, 5, 7}, 18) << "\n";
	//End

	//https://www.techiedelight.com/reverse-text-without-reversing-individual-words/
	std::string words = "Technical Interview Preparation";
	ReverseWordOrder(words);
	std::cout << words << std::endl;
	//End

	//https://www.geeksforgeeks.org/check-string-follows-order-characters-defined-pattern-not/
	if (StringMatchPattern("engineers rock","erk"))
	{
		std::cout << "TRUE\n";
	}
	else
	{
		std::cout << "FALSE\n";
	}
	//End

	// https://www.techiedelight.com/find-binary-strings-can-formed-given-wildcard-pattern/
	std::string binaryString = "1?11?00?1?";
	BinaryCombos(binaryString, std::vector<int>{}, 0);
	//End

	//https://www.techiedelight.com/find-peak-element-array/
	numbers = { 10, 8, 6, 5, 3, 2 };
	std::vector<int> PeakNumbers = FindPeakElements(numbers);
	std::cout << "The peak element('s) are ";
	for (int i = 0; i < PeakNumbers.size(); i++)
	{
		std::cout << PeakNumbers[i] << " ";
	}
	std::cout << std::endl;
	//End

	//https://www.techiedelight.com/maximum-sum-subarray-using-divide-conquer/
	numbers = { 20, -20, 1, 9, -6, 7, -3 };
	std::cout<< "The maximum sum of the subarray is: " << DACDFindMaxSum(numbers, 0, numbers.size() - 1) << "\n";
	//End

	//https://leetcode.com/problems/expression-add-operators/description/
	//End

	return 0;
}
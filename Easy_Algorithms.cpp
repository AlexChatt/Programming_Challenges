// Easy_Algorthims.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Easy_Algorthims.h"

void FindPairInArray(int Numbers[], int ArraySize, int target)
{
    std::unordered_map<int, int> NumTargets;
    bool FoundPair = false;

    for (int i = 0; i < ArraySize; i++)
    {
        int sum = target - Numbers[i];

        if (auto it = NumTargets.find(sum) != NumTargets.end())
        {
            std::cout << "Found Pair (" << Numbers[i] << "," << sum << ")\n";
            FoundPair = true;
        }

        NumTargets[Numbers[i]] = i;
    }

    if (!FoundPair)
    {
        std::cout << "Could not find Pair\n";
    }
}

void SortBinaryArray(int BinaryArray[], const int ArraySize)
{
    int zeroCount = 0;
    for (int i = 0; i < ArraySize; i++)
    {
        if (!BinaryArray[i])
        {
            zeroCount++;
        }
    }

    for (int i = 0; i < ArraySize; i++)
    {
        if (i < zeroCount)
        {
            BinaryArray[i] = 0;
        }
        else
        {
            BinaryArray[i] = 1;
        }
        std::cout << BinaryArray[i] << " ";
    }
    std::cout << "\n";
}

void MoveZerosToEnd(int NumsArray[], const int ArraySize)
{
    int* tmpArray = new int[ArraySize] {0};
    int tmpArrayIndex = 0;

    for (int i = 0; i < ArraySize; i++)
    {
        if (NumsArray[i] != 0)
        {
            tmpArray[tmpArrayIndex] = NumsArray[i];
            tmpArrayIndex++;
        }
    }

    memcpy(NumsArray, tmpArray, ArraySize * sizeof(int));
    delete [] tmpArray;
}

void GetMaxProductPair(std::vector<int>& nums)
{
    if (nums.size() <= 2)
    {
        return;
    }

    int Max1 = INT_MIN, Max2 = 0;
    int Min1 = INT_MAX, Min2 = 0;

    for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
    {
        if (*it > Max1)
        {
            Max1 = *it;
        }
        else if (*it > Max2)
        {
            Max2 = *it;
        }

        if (*it < Min1)
        {
            Min1 = *it;
        }
        else if (*it < Min2)
        {
            Min2 = *it;
        }
    }

    int MaxSum = 0, MinSum = 0;

    if (Max1 * Max2 > Min1 * Min2)
    {
        std::cout << Max1 << "," << Max2 << '\n';
    }
    else
    {
        std::cout << Min1 << "," << Min2 << '\n';
    }
}

void FindMajorityElement(std::vector<int>& Numbers)
{
    std::unordered_map<int, int> maxCount;
    int HighestKey, HighestValue = 0;

    for (std::vector<int>::iterator it = Numbers.begin(); it != Numbers.end(); ++it)
    {
        maxCount[*it]++;
        if (maxCount[*it] > HighestValue)
        {
            HighestKey = *it;
            HighestValue = maxCount[*it];
        }
    }

    if (maxCount[HighestKey] > std::floor(Numbers.size() / 2))
    {
        std::cout << HighestKey << " is the majority element\n";
    }
    else
    {
        std::cout << "No majority element found\n";
    }
}

void FindMaxSum(std::vector<int>& Numbers)
{
    int maxFound = INT_MIN;
    int maxEnding = 0;
    std::vector<int> subArray;

    int startingHighIndex = 0, endingHighIndex = 0;

    for (int i = 0; i < Numbers.size(); i++)
    {
        // update the maximum sum of subarray "ending" at index 'i' (by adding the
        // current element to maximum sum ending at previous index 'i-1')
        maxEnding = maxEnding + Numbers[i];

        // maximum sum should be more than the current element
        maxEnding = std::max(maxEnding, Numbers[i]);

        // update the result if the current subarray sum is found to be greater
        maxFound = std::max(maxFound, maxEnding);

        //Set our starting and ending index if we should
        if (maxFound == maxEnding)
        {
            if (maxEnding == Numbers[i])
            {
                startingHighIndex = i;
            }
            endingHighIndex = i;
        }
    }

    std::cout << "With subarray { ";
    for (int i = startingHighIndex; i <= endingHighIndex; i++)
    {
        std::cout << Numbers[i] << " ";
    }
    std::cout << "}, ";

    std::cout<<"Max sum found is "<< maxFound << '\n';
}

void OrderSwappedArray(std::vector<int>& Numbers)
{
    int lowIndex = -1, highIndex = -1;
    for (int i = 1; i < (Numbers.size() - 1); i++)
    {
        if (Numbers[i] > Numbers[i + 1])
        {
            if (highIndex == -1)
            {
                highIndex = i;
            }
            else
            {
                lowIndex = i + 1;
            }

        }

        if (lowIndex != -1 && highIndex != -1)
        {
            break;
        }
    }

    if (lowIndex != -1 && highIndex != -1)
    {
        int temp = Numbers[lowIndex];
        Numbers[lowIndex] = Numbers[highIndex];
        Numbers[highIndex] = temp;
    }

    std::cout << "Ordered List = ";
    for (std::vector<int>::iterator it = Numbers.begin(); it != Numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << '\n';
}

void GetMaxProductSubset(std::vector<int> Numbers)
{
    int Total = 1;
    // my first solution
    /*
    std::set<int> NegativeNumbers;
    std::vector<int> MaxProductNums;

    for (int i = 0; i < Numbers.size(); i++)
    {
        if (Numbers[i] < 0)
        {
            NegativeNumbers.insert(Numbers[i]);
        }
        else if (Numbers[i] != 0)
        {
            MaxProductNums.push_back(Numbers[i]);
            Total *= Numbers[i];
        }
    }

    if (NegativeNumbers.size() % 2 == 0)
    {
        for (std::set<int>::iterator it = NegativeNumbers.begin(); it != NegativeNumbers.end(); it++)
        {
            Total *= *it;
            MaxProductNums.push_back(*it);
        }
    }
    else if(NegativeNumbers.size() != 1)
    {
        for (std::set<int>::iterator it = NegativeNumbers.begin(); it != --NegativeNumbers.end(); it++)
        {
            Total *= *it;
            MaxProductNums.push_back(*it);
        }
    }*/

    // Fastest solution
    if (Numbers.size() == 0) {
        return;
    }
    else if (Numbers.size() == 1) {
        std::cout << "The maximum product of a subset is " << Numbers[0] << '\n';
    }

    int abs_min_so_far = INT_MAX;
    int negative = 0, positive = 0;

    for (int i = 0; i < Numbers.size(); i++)
    {
        if (Numbers[i] < 0)
        {
            negative++;
            if (abs_min_so_far > abs(Numbers[i])) { abs_min_so_far = abs(Numbers[i]); }
        }
        
        if (Numbers[i] != 0) 
        {
            Total = Total * Numbers[i];
        }
    }
    if (negative % 2 != 0) 
    {
        Total /= -abs_min_so_far;
    }

    std::cout << "The maximum product of a subset is " << Total << '\n';
}

void FindDiffPairs(std::vector<int> Numbers, int diffToFind)
{
    std::unordered_set<int> usedNumbers;
    std::sort(Numbers.begin(),Numbers.end());
    diffToFind = abs(diffToFind);

    std::cout << "Pairs: ";
    for (int i = 0; i < Numbers.size(); i++)
    {
        if (i + 1 >= Numbers.size() || Numbers[i] != Numbers[i + 1])
        {
            auto iter = usedNumbers.find(Numbers[i] - diffToFind);
            if (iter != usedNumbers.end())
            {
                std::cout << "(" << Numbers[i] << "," << *iter << ")" << " ";
            }

            usedNumbers.insert(Numbers[i]);
        }
    }

    std::cout << "\n";

}

void FindMinDiff(std::vector<int> Numbers, int I1, int I2)
{
    //my first solution
    /*
    std::vector<int> index1Found, index2Found;

    if (Numbers.size() <= 1) 
    {
      return;
    }

    for (int i = 0; i < Numbers.size(); i++) 
    {
        if (Numbers[i] == I1)
        {
            index1Found.push_back(i);
        }
        if (Numbers[i] == I2)
        {
            index2Found.push_back(i);
        }
    }

    if (index1Found.size() > 0 && index2Found.size() > 0)
    {
        sort(index1Found.begin(), index1Found.end());
        sort(index2Found.begin(), index2Found.end());

        int minDiff = abs(index1Found[0] - index2Found[0]);
        int maxDiff = abs(index1Found[index1Found.size() - 1] - index2Found[index2Found.size() - 1]);

        if (minDiff < maxDiff)
        {
            std::cout << "the min diff is " << minDiff << "\n";
        }
        else
        {
            std::cout << "the min diff is " << maxDiff << "\n";
        }
    }
    */

    // Best solution
    int x_index = Numbers.size(), y_index = Numbers.size();
    int min_diff = INT_MAX;

    // traverse the given array
    for (int i = 0; i < Numbers.size(); i++)
    {
        // if the current element is `x`
        if (Numbers[i] == I1)
        {
            // set `x_index` to the current index
            x_index = i;

            // if `y` is seen before, update the result if required
            if (y_index != Numbers.size()) 
            {
                min_diff = std::min(min_diff, abs(x_index - y_index));
            }
        }

        // if the current element is `y`
        if (Numbers[i] == I2)
        {
            // set `y_index` to the current index
            y_index = i;

            // if `x` is seen before, update the result if required
            if (x_index != Numbers.size()) 
            {
                min_diff = std::min(min_diff, abs(x_index - y_index));
            }
        }
    }
    std::cout << "the min diff is " << min_diff << "\n";
}

void PartitionArrays(std::vector<int> Numbers)
{
    if (Numbers.size() <= 1)
    {
        std::cout << "No subarray split possible \n";
        return;
    }

    int RightSizeTotal = 0;
    int LeftsizeTotal = 0;

    for (int i = 0; i < Numbers.size(); i++)
    {
        RightSizeTotal += Numbers[i];
    }

    for (int i = 0; i < Numbers.size(); i++)
    {
        LeftsizeTotal += Numbers[i];
        RightSizeTotal -= Numbers[i];
        if (LeftsizeTotal == RightSizeTotal)
        {
            std::copy(Numbers.begin(), Numbers.begin() + (++i), std::ostream_iterator<int>(std::cout, " "));
            std::cout << "\n";
            copy(Numbers.begin() + i, Numbers.end(), std::ostream_iterator<int>(std::cout, " "));
        }
    }
    std::cout << "\n";
}

void InsertionSort(int Numbers[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int j = i;
        int iValue = Numbers[i];

        while (j > 0 && Numbers[j - 1] > iValue)
        {
            Numbers[j] = Numbers[j - 1];
            j--;
        }

        Numbers[j] = iValue;
    }

    std::cout << "Sorted arry (Insertion Sort): { ";
    for (int i = 0; i < size; i++)
    {
        std::cout << Numbers[i] << " ";
    }
    std::cout << "}\n";
}

void SelectionSort(int Numbers[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int current = Numbers[i];
        int LowestNum = Numbers[i];
        int LowestIndex = i;

        for (int j = i+1; j < size; j++)
        {
            if (Numbers[j] < Numbers[i] &&
                Numbers[j] < LowestNum)
            {
                LowestNum = Numbers[j];
                LowestIndex = j;
            }
        }

        if (LowestIndex != i)
        {
            Numbers[i] = LowestNum;
            Numbers[LowestIndex] = current;
        }
    }

    std::cout << "Sorted array (Selection Sort): { ";
    for (int i = 0; i < size; i++)
    {
        std::cout << Numbers[i] << " ";
    }
    std::cout << "}\n";
}

void Merge(int Numbers[], int SortedNumbers[], int low, int mid, int high)
{
    int k = low, i = low, j = mid + 1;

    // while there are elements in the left and right runs
    while (i <= mid && j <= high)
    {
        if (Numbers[i] <= Numbers[j]) {
            SortedNumbers[k++] = Numbers[i++];
        }
        else {
            SortedNumbers[k++] = Numbers[j++];
        }
    }
    // copy remaining elements
    while (i <= mid) {
        SortedNumbers[k++] = Numbers[i++];
    }
    // No need to copy the second half (since the remaining items
    // are already in their correct position in the auxiliary array)

    // copy back to the original array to reflect sorted order
    for (int i = low; i <= high; i++) {
        Numbers[i] = SortedNumbers[i];
    }
}

void MergeSort(int Numbers[], int SortedNumbers[], int low, int high)
{
    if (high <= low) 
    { 
        return;
    }

    int mid = std::ceil((low + ((high - low)/2)));

    // recursively split runs into two halves until run size <= 1,
    // then merge them and return up the call chain

    MergeSort(Numbers, SortedNumbers, low, mid);          // split/merge left half
    MergeSort(Numbers, SortedNumbers, mid + 1, high);     // split/merge right half

    Merge(Numbers, SortedNumbers, low, mid, high);        // merge the two half runs.
}

void CountingSort(int Numbers[], int size, int maxNum)
{
    std::vector<int> Count;
    Count.insert(Count.begin(), maxNum+1, 0);

    for (int i = 0; i < size; i++)
    {
        Count[Numbers[i]]++;
    }

    int arrayPos = 0;
    for (int i = 0; i < maxNum+1; i++)
    {
        while (Count[i] > 0)
        {
            Numbers[arrayPos] = i;
            arrayPos++;
            Count[i]--;
        }
    }

    std::cout << "Sorted array (Counting Sort): { ";
    for (int i = 0; i < size; i++)
    {
        std::cout << Numbers[i] << " ";
    }
    std::cout << "}\n";

}

std::string RLE(std::string data)
{
    std::string RLEString = "";
    char Current = '\0';
    int count = 1;

    if (data.size() <= 0)
    {
        return "invalid";
    }
    Current = data[0];

    for (int i = 0; data[i]; i++)
    {
        if (data[i] == data[i+1])
        {
            count++;
        }
        else
        {
            RLEString += std::to_string(count) + data[i];
            count = 1;
        }
    }
    return RLEString;
}

bool traversalTree(node* root, int countdown)
{
    if(!root) {
        return false;
    }

    if (countdown == 1)
    {
        root->printNum();
        return true;
    }

    countdown--;
    traversalTree(root->Left, countdown);
    traversalTree(root->Right, countdown);
}

node* insertInTree(node* root, int key)
{
    if (!root)
    {
        return new node(key);
    }

    if (key < root->number)
    {
        root->Left = insertInTree(root->Left, key);
        //node* newnode = insertInTree(root->Left, key);
        //if (root->Left == NULL)
        //{
        //   root->Left = newnode;
        //}
    }
    else
    {
        root->Right = insertInTree(root->Right, key);
        //node* newnode = insertInTree(root->Right, key);
        //if (root->Right == NULL)
        //{
            //root->Right = newnode;
        //}
    }

    return root;
}

void PrintTree(node* root)
{
    if (!root) { return; }

    if (root->Left)
    {
        PrintTree(root->Left);
    }
    std::cout << root->number << " ";
    if (root->Right)
    {
        PrintTree(root->Right);
    }
}

void RotateArrayLeft() 
{
    int Array[] = {1,2,3,4,5};
    int ArraySize = sizeof(Array) / sizeof(int);
    int tmp = Array[0];

    for (int i = 0; i < ArraySize - 1; i++)
    {
        Array[i] = Array[i + 1];
    }
    Array[ArraySize - 1] = tmp;
}

void RotateArrayRight()
{
    int Array[] = { 1,2,3,4,5 };
    int ArraySize = sizeof(Array) / sizeof(int);
    int tmp = Array[ArraySize - 1];

    for (int i = ArraySize - 1; i > 0; i--)
    {
        Array[i] = Array[i - 1];
    }
    Array[0] = tmp;
}

void ReverseArray(int Numbers[], int size)
{
    int i1 = 0, i2 = size - 1;

    while (i1 < i2)
    {
        int tmp = Numbers[i1];
        Numbers[i1] = Numbers[i2];
        Numbers[i2] = tmp;

        i1++; i2--;
    }

    std::cout << "Reverse Array: { ";
    for (int i = 0; i < size; i++)
    {
        std::cout << Numbers[i] << " ";
    }
    std::cout << "}\n";
}

void ElementsHigherThenRight(int Numbers[], int size)
{
    std::vector<int> HigherNums;
    int CurrentMax = Numbers[size - 1];
    HigherNums.push_back(CurrentMax);

    for (int i = size - 2; i >= 0; i--)
    {
        if (Numbers[i] > CurrentMax)
        {
            HigherNums.push_back(Numbers[i]);
        }
        CurrentMax = std::max(CurrentMax, Numbers[i]);
    }

    std::cout << "The elements that are greater than all elements to their right are: ";
    for (int i = 0; i < HigherNums.size(); i++)
    {
        std::cout << HigherNums[i] << " ";
    }
    std::cout << "\n";
}

int runEFunctions()
{
    // https://www.techiedelight.com/find-pair-with-given-sum-array/
    int nums[] = { 8, 7, 2, 5, 3, 1 };
    int numsSize = sizeof(nums) / sizeof(int);
    int target = 10;
    FindPairInArray(nums, numsSize, target);
    // End

    // https://www.techiedelight.com/sort-binary-array-linear-time/
    int binaryArray[] = { 1, 0, 1, 0, 1, 0, 0, 1 };
    int numberSize = sizeof(binaryArray) / sizeof(int);
    SortBinaryArray(binaryArray, numberSize);
    // End

    // https://www.techiedelight.com/move-zeros-present-array-end/
    int numberArray[] = { 6, 0, 8, 2, 3, 0, 4, 0, 1 };
    numberSize = sizeof(numberArray) / sizeof(int);
    MoveZerosToEnd(numberArray, numberSize);
    // End

    // https://www.techiedelight.com/find-maximum-product-two-integers-array/
    std::vector<int> Nums = { 10, -3, 5, 6, -2 };
    GetMaxProductPair(Nums);
    // End

    //https://www.techiedelight.com/find-majority-element-in-an-array-boyer-moore-majority-vote-algorithm/
    Nums = { 2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2 };
    FindMajorityElement(Nums);
    // End

    //https://www.techiedelight.com/maximum-subarray-problem-kadanes-algorithm/
    Nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    FindMaxSum(Nums);
    // End

    //https://www.techiedelight.com/sort-array-using-one-swap/
    Nums = { 3, 8, 6, 7, 5, 9 };
    OrderSwappedArray(Nums);
    // End

    //https://www.techiedelight.com/maximum-product-subset-problem/
    Nums = { -6, 4, -5, 8, -10, 0, 8 };
    GetMaxProductSubset(Nums);
    // End

    //https://www.techiedelight.com/find-pairs-with-given-difference-array/
    Nums = { 1, 5, 2, 2, 2, 5, 5, 4 };
    int k = -3;
    FindDiffPairs(Nums, k);
    // End

    //https://www.techiedelight.com/find-minimum-difference-index-two-given-elements-present-array/
    Nums = { 1, 3, 5, 4, 8, 2, 4, 3, 6, 5 };
    int x = 2, y = 3;
    FindMinDiff(Nums, x, y);
    // End

    //https://www.techiedelight.com/partition-array-into-two-sub-arrays-with-same-sum/
    Nums = { 6, -4, -3, 2, 3 };
    PartitionArrays(Nums);
    // End

    //https://www.techiedelight.com/insertion-sort-iterative-recursive/
    int Insertnums[] = { 3, 8, 5, 4, 1, 9, -2 };
    numsSize = sizeof(Insertnums) / sizeof(int);
    InsertionSort(Insertnums, numsSize);
    // End

    //https://www.techiedelight.com/insertion-sort-iterative-recursive/
    int InsertSelectnums[] = { 3, 8, 5, 4, 1, 9, -2 };
    numsSize = sizeof(InsertSelectnums) / sizeof(int);
    SelectionSort(InsertSelectnums, numsSize);
    // End

    //https://www.techiedelight.com/merge-sort/
    int arr[10], aux[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        aux[i] = arr[i] = (rand() % 100) - 50;
    }
    MergeSort(arr, aux, 0, 10-1);

    std::cout << "Sorted array (Merge Sort): { ";
    for (int i = 0; i < 10; i++)
    {
        std::cout << aux[i] << " ";
    }
    std::cout << "}\n";
    //End

    //https://www.techiedelight.com/counting-sort-algorithm-implementation/
    int CountSelectnums[] = { 4, 2, 10, 10, 1, 4, 2, 1, 10 };
    numsSize = sizeof(CountSelectnums) / sizeof(int);
    CountingSort(CountSelectnums, numsSize, 10);
    //End

    // https://www.techiedelight.com/run-length-encoding-rle-data-compression-algorithm/
    std::string Line = "ABBCCCD";
    std::string RLEcom = RLE(Line);
    std::cout << "RLEcom = " << RLEcom << '\n';
    // End

    // https://www.techiedelight.com/level-order-traversal-binary-tree/
    node* root = new node(15);
    root->Left = new node(10);
    root->Right = new node(20);
    root->Left->Left = new node(8);
    root->Left->Right = new node(12);
    root->Right->Left = new node(18);
    root->Right->Right = new node(25);

    int printRow = 0;
    do
    {
        printRow++;
        std::cout << "\nRow " << printRow << " of the tree contains : ";
    } while (traversalTree(root, printRow));
    delete root;
    std::cout << "\n";
    //End

    // https://www.techiedelight.com/insertion-in-bst/
    // not finished yet, should be able to make whole tree +
    // Print from left to right
    root = nullptr;
    std::vector<int> numbers = { 15, 10, 20, 8, 12, 16, 25 };
    for (int i = 0; i < numbers.size(); i++)
    {
        root = insertInTree(root, numbers[i]);
    }
    PrintTree(root);
    std::cout << "\n";
    //End

    //https://www.techiedelight.com/reverse-an-array-cpp/
    int Reversenums[] = { 1,2,3,4,5,6 };
    numsSize = sizeof(Reversenums) / sizeof(int);
    ReverseArray(Reversenums, numsSize);
    //End

    //https://www.techiedelight.com/find-elements-array-greater-than-elements-right/
    int Elements[] = { 10, 4, 6, 3, 5 };
    numsSize = sizeof(Elements) / sizeof(int);
    ElementsHigherThenRight(Elements, numsSize);
    //End

    //Rotate Arrays Left and Right
    RotateArrayLeft();
    RotateArrayRight();
    //End

    return 0;
}


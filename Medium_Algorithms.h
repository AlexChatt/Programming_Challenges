#pragma once

#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iterator>
#include <tuple>
#include <stack>
#include "Utility.h"

//Utility functions
void swapInt(std::vector<int>& nums, int I1, int I2);
void swapIntTwoVectors(std::vector<int>& nums1, std::vector<int>& nums2, int I1, int I2);

// Solution functions
bool DetectSubArrayZero(int Numbers[], int size);
std::vector<int> LargestSubArrayToTarget(std::vector<int> nums, int target);
void FindAllZeroSubArrays(std::vector<int> nums);
void Sort012Array(std::vector<int> &nums);
void inPlaceTwoArrayMerge(std::vector<int>& nums1, std::vector<int>& nums2);
void inPlaceTwoArrayMergeConstraints(std::vector<int>& nums1, std::vector<int>& nums2);
void largestSubarray01(std::vector<int>& nums);
void ProductReplace(std::vector<int>& nums);
void largestsubarrayConInts(std::vector<int> nums);
void FindMaxDiff(std::vector<int> nums);
void LongestBitonicSubArray(std::vector<int> nums);
void FindMaxContinuesSubArray(std::vector<int> nums);
void MaxSequeceOnes(std::vector<int> nums, int k);
void PrintAllCombos(std::vector<int> nums, int k);
void FindMinSubArrayOfSize(std::vector<int> nums, int k);
void FindSubArrayWithSum(std::vector<int> nums, int target);
void MaxStockProfit(std::vector<int> nums);
void MaxPlatformsNeeded(std::vector<double> arrive, std::vector<double> depart);
void SubArrayRevert(std::vector<int> nums, int SI, int EI, int m);
std::tuple<int,int,int> FindSortedTriplet(std::vector<int> nums);
void IncreasingSubArrays(std::vector<int> nums);
void FindMinMovesToZero(std::vector<int> nums);
void FindPairForSumInCir(std::vector<int> nums, int sum);
void FindTripletToSum(std::vector<int> nums, int sum);
int PowerOf2Higher(int number);
int PowerOf2Lower(int number);
void FrequencySort(std::vector <int> &numbers);
std::vector<std::vector<int>> FindAllDistinctCombos(std::vector<int> nums, int k);

// Backtracking algorithm example
std::vector<std::vector<int>> GetAllAddedCombos(int number);
void AddedCombosSolve(std::vector<int>& curNums, int num, int current, std::vector<std::vector<int>> &allCombos);
//End

// Inorder Tree Traversal
void TraverseOrderTree(node<int>* Root);
// End
// Preorder Tree Traversal
void TraversePreOrderTree(node<int>* Root);
// End
// Postorder Tree Traversal
void TraversePostOrderTree(node<int>* Root);
// End
// Cousin Check
bool TreeCousinCheck(node<int>* Root, node<int>*N1, node<int>*N2);
bool FindNodeDepth(node<int>* Root, node<int>* Node, int Depth, int& FoundDepth);
// End
// sum tree check
bool CheckIfSumTree(node<int>* Root);
int SumNodes(node<int>* Node);
// End
// Diameter of a binary tree
int GetTreeDimention(node<int>* Root);
int CountPath(node<int>* Node);
// End

std::vector<std::vector<int>> GetAllTripToSum(std::vector<int> nums, int target);
void TripleSum(std::vector<int> numbers, std::vector<int>& curTrip, int& remaining, int curIndex, std::vector<std::vector<int>>& allCombos);

int Partition(std::vector<int> &nums, int start, int end);
void Quicksort(std::vector<int> &nums, int start, int end);
bool TupleFrequencySort(std::tuple<int, int, int>& t1, std::tuple<int, int, int>& t2);
bool LargestNumberSort(int n1, int n2);
int CycleElements(std::vector<int> array, int& elhit, int k);

std::pair<int, int> closestPair(std::vector<int> n1, std::vector<int> n2, int target);
std::vector <int> AltPosNeg(std::vector<int> numbers);

void ShuffleInPlace(std::vector<int> &nums, std::vector<int> pos);
void FindSymPairs(std::vector<std::pair<int,int>> pairs);

void FindNoneOverlappingPairs(std::vector<int> numbers);
void LargestSumBetweenVectors(std::vector<int> v1, std::vector<int> v2);
void SortByOccurence(std::vector<int> &numbers);

bool ConsecutiveInts(std::vector<int> numbers, int &min, int &max);
void DecodeArray(std::vector<int> numbers);
void CountDistinctAbsolutes(std::vector<int> numbers);
void CountDistinctAbsolutesNoSet(std::vector<int> numbers);

bool IndexOverlapCheck(std::pair<int, int> p1, std::pair<int, int> p2);
void FourSumProblem(std::vector<int> numbers, int target);

bool IsMovesCirclar(std::string moves);

void FindMinRemovals(std::vector<int> numbers);

bool IsIsomorphicString(std::string S1, std::string IS);
void RemoveSpaces(std::string &s1);
void StringPatternMatch(std::vector<std::string> strings, std::string patternString);
void GroupAnagrams(std::vector<std::string> strings);
void EditsToString(std::string current, std::string target);
void PrintZigZagString(std::string string, int k);
void LongestSubString(std::string string);
void PermutationStringOfSub(std::string string, std::string substring);
void PrintCombos(std::vector<std::vector<std::string>> Strings);
int BalanceInversionsNeeded(std::string Expression);
void PrintBalenceBracketCombos(std::string current, int open, int n, int OpenUsed);
void FindFirstNonRepeatChar(std::string string);
void FindLongestPal(std::string s);
void PrintNonOverlapSubStrings(std::string s, int index, std::vector<std::vector<std::string>>& combinations, std::vector<std::string> current);
void StringDiff(std::string X, std::string Y);
int KnapSackProblem(std::vector<int> value, std::vector<int> weight, int CurWeight, int curri, std::map <std::string, int> lookup);
int RobCuttingProfit(std::vector<int> length, std::vector<int> price, int CurLen, int StartI);
int EvaluateMathExpression(std::string Equation);
int MinCoinChange(std::vector<int> validCoins, int MoneyLeft);
int MinCoinChangeDynamic(std::vector<int> validCoins, int MoneyLeft);
void ReverseWordOrder(std::string& words);
bool StringMatchPattern(std::string word, std::string pattern);
void BinaryCombos(std::string original, std::vector<int> current, int index);
std::vector<int> FindPeakElements(std::vector<int> numbers);
void BSACheckPeak(int min, int mid, int max, std::vector<int> numbers, std::vector<int>& PeakNums);
int DACDFindMaxSum(std::vector<int> nums, int low, int high);
int runMFunctions();

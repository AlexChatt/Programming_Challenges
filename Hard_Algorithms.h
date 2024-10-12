#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <string>
#include <ctime> 
#include "Utility.h"

int FindIndexMaxLenght(std::vector<int> numbers);
int MaxSumInCirArray(std::vector<int> numbers);
int MaxProductSubarray(std::vector<int> numbers);
int GetTrappedRainAmount(std::vector<int> numbers);
int LongestLengthSameSum(std::vector<int> X, std::vector<int> Y);
void InPlaceArrange(std::vector<int>& numbers);
int FindMaxDiffSubArrays(std::vector<int> numbers);
int GetMinOrMaxNum(std::vector<int> numbers, int &RestrictStart, int &RestrictEnd, bool bFindMax);

std::vector<std::vector<int>> GetAllPosCombos(int N);
void FillCombos(std::vector<std::vector<int>>& combos, int N, int Sum, std::vector<int> currentList);

std::pair<int,int> FindMinRange3(std::vector<int> n1, std::vector<int> n2, std::vector<int> n3);

void partition(std::vector<int> const& S);
bool isSubsetExist(std::vector<int> const& S, int n, int a, int b, int c, std::vector<int>& arr);

int InverseCountMergeSort(std::vector<int>& arr, std::vector<int>& aux, int low, int high);
int InverseCountMergeS(std::vector<int>& arr, std::vector<int>& aux, int low, int mid, int high);

int runHFunctions();

#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <ctime> 
#include "Utility.h"


void FindPairInArray(int Numbers[], int ArraySize, int target);
void SortBinaryArray(int BinaryArray[], const int ArraySize);
void MoveZerosToEnd(int NumsArray[], const int ArraySize);
void GetMaxProductPair(std::vector<int>& nums);
void FindMajorityElement(std::vector<int>& Numbers);
void FindMaxSum(std::vector<int>& Numbers);
void GetMaxProductSubset(std::vector<int> Numbers);
void FindDiffPairs(std::vector<int> Numbers, int diffToFind);
void FindMinDiff(std::vector<int> Numbers, int I1, int I2);
void PartitionArrays(std::vector<int> Numbers);
void InsertionSort(int Numbers[], int size);
void SelectionSort(int Numbers[], int size);
void MergeSort(int Numbers[], int SortedNumbers[], int low, int high);
void CountingSort(int Numbers[], int size, int maxNum);
std::string RLE(std::string data);
bool traversalTree(node* root, int countdown);
node* insertInTree(node* root, int key);
void PrintTree(node* root);
void ReverseArray(int Numbers[], int size);
void ElementsHigherThenRight(int Numbers[], int size);

int runEFunctions();
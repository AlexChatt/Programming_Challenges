#pragma once
#include <iostream>
#include <vector>
#include <algorithm> 
#include <numeric>
#include "graph.h"
#include "utility.h"


int BinaryChopNonRecursive(std::vector<int> SortedNums, int NumToFind);

//https://favtutor.com/blogs/backtracking-algorithm-problems-cpp#:~:text=What%20is%20Backtracking%3F,choose%20the%20most%20optimal%20one.
std::vector<std::vector<int>> BackTrackExample(std::vector<int> SortedNums, int Target);
void BackTrackCombinations(std::vector<int> candidates, int target, int ind, std::vector<std::vector<int>>& ans, std::vector<int> current);

//https://www.techiedelight.com/k-partition-problem-print-all-subsets/
void KPartitions(std::vector<int> const& S, const int split);
bool isSubsetExist(std::vector<int> const& S, int n, std::vector<int> tracker, std::vector<int>& arr);

//https://www.techiedelight.com/merge-sort/
void MergeSort(std::vector<int> &arr, std::vector<int> &aux, int low, int high);
void MergeS(std::vector<int> &arr, std::vector<int> &aux, int low, int mid, int high);

int runAlgFunctions();

//https://en.wikipedia.org/wiki/Huffman_coding
bool paircomp(const std::pair<int, node<std::string>*>& a, const std::pair<int, node<std::string>*>& b);
node<std::string>* ConstructHuffmanTree(std::string word);
std::string GetIdFromHuffmanTree(node<std::string>* root, std::string text);
std::string GetTextFromHuffmanTree(node<std::string>* root, std::string text);
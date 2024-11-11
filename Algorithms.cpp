#include "Algorithms.h"

int BinaryChopNonRecursive(std::vector<int> SortedNums, int NumToFind)
{
	int min = 0, mid, max = SortedNums.size()-1;
	int IndexFound = -1;
	mid = std::ceil((max + min) / 2);

	if (SortedNums.size() <= 0)
	{
		return -1;
	}

	while (min < max)
	{
		if (SortedNums[min] == NumToFind)
		{
			IndexFound = min;
			break;
		}
		else if (SortedNums[mid] == NumToFind)
		{
			IndexFound = mid;
			break;
		}
		else if(SortedNums[max] == NumToFind)
		{
			IndexFound = max;
			break;
		}

		if (NumToFind < SortedNums[mid])
		{
			max = mid-1;
		}
		else
		{
			min = mid+1;
		}
		mid = std::ceil((max + min) / 2);
	}
	
	return IndexFound;
}

std::vector<std::vector<int>> BackTrackExample(std::vector<int> SortedNums, int Target)
{
	std::vector<std::vector<int>> Combos;
	
	BackTrackCombinations(SortedNums, Target, 0, Combos, std::vector<int>());

	return Combos;
}

void BackTrackCombinations(std::vector<int> candidates, int target, int ind, std::vector<std::vector<int>>& ans, std::vector<int> current)
{
	if (target == 0)
	{
		ans.push_back(current);
	}
	if (target < 0)
	{
		return;
	}

	for (int i = ind; i < candidates.size(); i++)
	{
		current.push_back(candidates[i]);
		BackTrackCombinations(candidates, target - candidates[i], i+1, ans, current);
		current.pop_back();
	}

	return;
}

void KPartitions(std::vector<int> const& S, const int split)
{
	std::vector<int> storage(S.size());

	int totalSum = std::accumulate(S.begin(), S.end(), 0);
	bool PossiblePart = true;

	if (totalSum % split || S.size() < split)
	{
		PossiblePart = false;
	}
	else
	{
		std::vector<int> tracker(split, totalSum/split);
		PossiblePart = isSubsetExist(S, S.size()-1, tracker, storage);
	}

	if (!PossiblePart)
	{
		std::cout << "Partition by " << split << " is not possible";
		return;
	}

	// print the partitions
	for (int i = 0; i < split; i++)
	{
		std::cout << "Partition " << i << " is ";
		for (int j = 0; j < storage.size(); j++)
		{
			if (storage[j] == i + 1) {
				std::cout << S[j] << " ";
			}
		}
		std::cout << std::endl;
	}
	

}

bool isSubsetExist(std::vector<int> const& S, int n, std::vector<int> tracker, std::vector<int>& arr)
{
	bool bAllZero = true, bParFound = false;

	for (int i = 0; i < tracker.size(); i++)
	{
		if (tracker[i])
		{ 
			bAllZero = false; 
			break;
		}
	}
	if (bAllZero) { return true; }

	if (n < 0) {
		return false;
	}

	for (int i = 0; i < tracker.size(); i++)
	{
		if (tracker[i] - S[n] >= 0)
		{
			arr[n] = i+1;
			tracker[i] -= S[n];
			bParFound = isSubsetExist(S, n - 1, tracker, arr);
			tracker[i] += S[n];
		}

		if (bParFound)
		{
			break;
		}
	}

	return bParFound;
}

void MergeSort(std::vector<int> &arr, std::vector<int> &aux, int low, int high)
{
	if (high <= low)
	{
		return;
	}

	int mid = (low + ((high - low) >> 1));

	MergeSort(arr, aux, low, mid);
	MergeSort(arr, aux, mid + 1, high);

	MergeS(arr, aux, low, mid, high);
}

void MergeS(std::vector<int> &arr, std::vector<int> &aux, int low, int mid, int high)
{
	int k = low, i = low, j = mid + 1;

	while (i <= mid && j <= high)
	{
		if (arr[i] <= aux[j])
		{
			aux[k++] = arr[i++];
		}
		else
		{
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
}

bool paircomp(const std::pair<int, node<std::string>*>& a, const std::pair<int, node<std::string>*>& b)
{
	return a.first < b.first;
}

node<std::string>* ConstructHuffmanTree(std::string word)
{
	std::unordered_map<char, int> chars;
	std::vector<std::pair<int, node<std::string>*>> nodes;

	if (word.size() == 0) { return nullptr; }

	for (int i = 0; i < word.size(); i++)
	{
		if (chars.find(word[i]) == chars.end())
		{
			chars[word[i]] = 1;
		}
		else
		{
			chars[word[i]]++;
		}
	}

	for (auto& Item : chars)
	{
		node<std::string>* NewNode = new node<std::string>(std::string{ Item.first });
		nodes.push_back(std::pair<int, node<std::string>*>(Item.second, NewNode));
	}

	while (nodes.size() > 1)
	{
		std::sort(nodes.begin(), nodes.end(), paircomp);
		int comNum = nodes[0].first + nodes[1].first;
		std::string comString = nodes[0].second->getValue() + nodes[1].second->getValue();
		node<std::string>* NewNode = new node<std::string>(comString);
		NewNode->Left = nodes[0].second;
		NewNode->Right = nodes[1].second;
		nodes.erase(nodes.begin());
		nodes.erase(nodes.begin());
		nodes.push_back(std::pair<int, node<std::string>*>(comNum, NewNode));
	}

	return nodes[0].second;
}

std::string GetIdFromHuffmanTree(node<std::string>* root, std::string text)
{
	std::string TextToBinary = "";
	node<std::string>* CurrentNode = root;

	for (int i = 0; i < text.size(); i++)
	{
		std::string currentCode = "";
		CurrentNode = root;
		while (true)
		{
			if (CurrentNode->value == std::string{ text[i] })
			{
				TextToBinary += currentCode;
				break;
			}
			if (CurrentNode->Left && CurrentNode->Left->value.find(text[i]) != std::string::npos)
			{
				currentCode += "0";
				CurrentNode = CurrentNode->Left;
			}
			else if (CurrentNode->Right && CurrentNode->Right->value.find(text[i]) != std::string::npos)
			{
				currentCode += "1";
				CurrentNode = CurrentNode->Right;
			}
			else
			{
				std::cout << "Error: Huffman Tree does not contain letter " << text[i] << "\n";
				break;
			}
		}
	}
	return TextToBinary;
}

std::string GetTextFromHuffmanTree(node<std::string>* root, std::string text)
{
	std::string BinaryToText = "";
	node<std::string>* CurrentNode = root;

	for (int i = 0; i < text.size(); i++)
	{
		if (CurrentNode->value.size() > 1)
		{
			if (text[i] == '0')
			{
				CurrentNode = CurrentNode->Left;
			}
			else if (text[i] == '1')
			{
				CurrentNode = CurrentNode->Right;
			}
			else
			{
				std::cout << "Error: None binary value detect " << text[i] << "\n";
				break;
			}
		}

		if (CurrentNode->value.size() == 1)
		{
			BinaryToText += CurrentNode->value;
			CurrentNode = root;
		}
	}

	return BinaryToText;
}

int runAlgFunctions()
{
	std::vector<int> numbers = { 1,3,5,6,9,10,13,16,19,23,26,29,32,35,39,40,42,45,78,100};
	int numberToFind = 19;
	int index = BinaryChopNonRecursive(numbers, numberToFind);
	std::cout << "We found " << numberToFind << " at index " << index << std::endl;

	numbers = { 1, 3, 5, 7, 8, 12, 14, 15 };
	int target = 15;
	std::vector<std::vector<int>> NumsToTarget = BackTrackExample(numbers, target);

	numbers = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };
	int split = 2;
	std::sort(numbers.begin(), numbers.end());
	KPartitions(numbers, split);

	numbers = { 10, 4, -2, 1, 300, 250, -12, -6, 100, -100, 50, -5 };
	std::vector<int> holder = numbers;
	MergeSort(numbers, holder, 0, numbers.size()-1);

	Graph G1;
	G1.addEdge(gNode("Jack", false), gNode("Bill", false), false, 1);
	G1.addEdge(gNode("Jack", false), gNode("Phil", false), false, 1);
	G1.addEdge(gNode("Jack", false), gNode("Sarah", false), false, 1);
	G1.addEdge(gNode("Bill", false), gNode("John", false), false, 1);
	G1.addEdge(gNode("Bill", false), gNode("Nat", true), false, 1);
	G1.printAdjList();
	std::string salesmen = "\0";
	G1.breathFirstMango("Jack", salesmen);

	node<std::string>* root = ConstructHuffmanTree("hello");
	std::string Binarycode = GetIdFromHuffmanTree(root, "hello");
	std::string OriginalString = GetTextFromHuffmanTree(root, Binarycode);
	std::cout << "Original Text = " << OriginalString << ". Binary Code = " << Binarycode << std::endl;
	delete root;

	return 0;
}

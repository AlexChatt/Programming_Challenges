#pragma once
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <unordered_map>
#include <iostream>

struct gNode
{
	std::string name = "N/A";
	bool bMangoSeller = false;

	gNode(std::string n, bool bManSeller )
	{
		name = n;
		bMangoSeller = bManSeller;
	}
};

class Graph
{
private:
	std::unordered_map<std::string, std::list<std::pair<gNode,int>>> mGraph;

public:
	void addEdge(gNode n1, gNode n2, bool bidir, int distance);

	void printAdjList();

	bool breathFirstMango(std::string StartingName, std::string& salesmen);
};

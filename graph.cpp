#include "graph.h"

void Graph::addEdge(gNode n1, gNode n2, bool bidir, int distance)
{
	mGraph[n1.name].push_back(std::make_pair(n2, distance));

	if (bidir)
	{
		mGraph[n2.name].push_back(std::make_pair(n1, distance));
	}
}

void Graph::printAdjList()
{
	for (auto nodes : mGraph)
	{
		std::string NodeName = nodes.first;
		std::list<std::pair<gNode, int>> neighbours = nodes.second;

		std::cout << NodeName << "->";
		for (auto neighbour : neighbours)
		{
			std::string dest = neighbour.first.name;
			int dist = neighbour.second;

			std::cout << dest << " " << dist << ",";
		}
		std::cout << std::endl;
	}
}

bool Graph::breathFirstMango(std::string StartingName, std::string& salesmen)
{
	std::set<std::string> visited;
	std::queue<gNode> searchList;

	if (mGraph.find(StartingName) == mGraph.end())
	{
		return false;
	}

	for (auto gnode : mGraph[StartingName])
	{
		searchList.push(gnode.first);
	}

	while (searchList.size() > 0)
	{
		gNode Person = searchList.front();
		searchList.pop();

		if (Person.bMangoSeller)
		{
			salesmen = Person.name;
			return true;
		}

		if (mGraph.find(Person.name) != mGraph.end())
		{
			for (auto gnode : mGraph[Person.name])
			{
				if (visited.find(gnode.first.name) == visited.end())
				{
					searchList.push(gnode.first);
				}
			}
		}

		visited.insert(Person.name);
	}

	return false;
}

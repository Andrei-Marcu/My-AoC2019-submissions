#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <map>
#include <vector>
#include <queue>
#include <bitset>
#include <set>

#define YOU '@'
#define CLR '.'
#define OBS '#'
#define OFFSET ('a' - 'A')
#define NRKEYS ('z' - 'a' + 1)

using namespace std;

//
//
//
//
//	DAY 18 IS NOT WORKING!!!
//
//
//
//

ifstream fin("input.txt");
ofstream fout("output.txt");

//I did this because I wasn't sure if I was going to make a class
typedef char Node;

typedef pair<int, int> coord;

inline bool isDoor(Node node) {
	return 'A' <= node && node <= 'Z';
}

inline bool isKey(Node node) {
	return 'a' <= node && node <= 'z';
}

struct Graph
{
	size_t distance;
	bitset<NRKEYS> keys;
	map<Node, map<Node, size_t>>adjacency;
	Node node;

	void insert(Node a, Node b, size_t dist) {
		//debug
		if (isDoor(b) && !isDoor(a))
			;// throw;
		else
			adjacency[a].emplace(b, dist);
	}

	bool isEgde(Node a, Node b) {
		auto& adj = adjacency[a];
		return adj.find(b) != adj.end();
	}

	void update(Node a, Node b, size_t dist) {
		//if (isKey(b)) {
		if (isEgde(a, b)) {
			auto& iniDist = adjacency[a][b];
			if (dist < iniDist) {
				iniDist = dist;
			}
		}
		else
		{
			insert(a, b, dist);
		}
		//}
		/*if (isKey(a)) {
			if (isEgde(b, a)) {
				auto& iniDist = adjacency[b][a];
				if (dist < iniDist) {
					iniDist = dist;
				}
			}
			else
			{
				insert(b, a, dist);
			}
		}*/
	}

	/*void insertBidir(Node a, Node b, size_t dist) {
		adjacency[a].emplace(b, dist);
		adjacency[b].emplace(a, dist);
	}*/

	void unlock() {
		if (isKey(node)) {
			keys[node - 'a'] = 1;
			Node door = node - OFFSET;
			auto& adjacents = adjacency[door];


			for (auto& a : adjacents)
			{
				for (auto& b : adjacents)
				{
					if (a.first != b.first /*&& isKey(b.first)*/)
						update(a.first, b.first, a.second + b.second);
				}
			}
			for (auto& each : adjacency)
			{
				each.second.erase(node);
				each.second.erase(door);
			}
			adjacency.erase(door);
			/*for (auto& key : adjacency[node])
			{
				adjacency[key.first].erase(node);
			}*/
		}
	}

	//comparison reversed as priority queues are prioritizing elements considered larger
	const bool operator<(const Graph& rhs) const {
		if (distance == rhs.distance) {
			return keys.count() > rhs.keys.count();
		}
		return distance > rhs.distance;
	}

	/*const bool operator<(const Graph& rhs) const {
		if (keys.count() == rhs.keys.count()) {
			return distance > rhs.distance;
		}
		return keys.count() > rhs.keys.count();
	}*/

	bool operator()(Graph* lhs, Graph* rhs) {
		return *lhs < *rhs;
	}

}iniGraph;

vector<string> area;

const coord nullCoord = coord(0, 0);

coord operator+(coord& lhs, coord& rhs) {
	return { lhs.first + rhs.first,lhs.second + rhs.second };
}

Node getNode(coord& pos) {
	return area[pos.first][pos.second];
}

coord directions[] = {
	{-1,0},
	{0,1},
	{1,0},
	{0,-1}
};

coord positions[255];
bitset<NRKEYS> allKeys;

set<Node> doorStack;

//Advent of Code is Minecaft
void registerDoor(Node door, coord pos) {
	//Already registered doors will be ignored
	if (positions[door] != pos) {
		positions[door] = pos;
		doorStack.insert(door);
	}
}

void spread(map<coord, bool>& explored, queue<pair<coord, int>>& toExpl, coord& pos, size_t dist) {
	for (auto& dir : directions)
	{
		auto neighbor = pos + dir;
		if (getNode(neighbor) != OBS && !explored[neighbor]) {
			toExpl.emplace(neighbor, dist);
		}
	}
}

void bfs(coord& start) {
	Node n1 = getNode(start);

	map<coord, bool> explored;

	//location distance
	queue<pair<coord, int>> toExpl;

	explored[start] = 1;
	spread(explored, toExpl, start, 1);

	while (!toExpl.empty())
	{
		auto expl = toExpl.front();
		toExpl.pop();
		auto& pos = expl.first;
		if (explored[pos])
		{
			continue;
		}
		explored[pos] = 1;
		auto& dist = expl.second;
		auto n2 = getNode(pos);
		if (isDoor(n2)) {
			if (n1 != YOU) {
				//we don't care about reaching the door because it's locked, but we care about what the door is reaching when we unlock it.
				//if both are doors then when we bfs the second door the path is going to be bidirectional;
				iniGraph.insert(n2, n1, dist);
			}
			registerDoor(n2, pos);
		}
		else // if it's not a door we also continue the bfs
		{
			if (isKey(n2)) {
				//bfs of the second key will make this bidirectional if n1 a key
				iniGraph.insert(n1, n2, dist);
				positions[n2] = pos;
				allKeys[n2 - 'a'] = 1;
			}

			spread(explored, toExpl, pos, dist + 1);
		}
	}
}

int main() {
	auto& start = positions[YOU];
	string s;
	while (fin >> s)
	{
		if (start == nullCoord && s.find(YOU) != -1) {
			start.first = area.size();
			start.second = s.find(YOU);
		}
		area.emplace_back(s);
	}
	iniGraph.node = YOU;
	iniGraph.distance = 0;

	bfs(start);

	while (!doorStack.empty())
	{
		auto it = doorStack.begin();
		Node door = *it;
		doorStack.erase(it);
		bfs(positions[door]);
	}

	for (Node i = 'a'; i <= 'z'; i++)
	{
		if (positions[i] != nullCoord)
			bfs(positions[i]);
	}

	priority_queue<Graph*, vector<Graph*>, Graph> graphs;
	graphs.push(&iniGraph);

	while (!graphs.empty())
	{
		auto top = graphs.top();
		graphs.pop();
		top->unlock();
		if (top->keys == allKeys) {
			cout << top->distance;
			break;
		}
		else {
			//auto dist = top->distance;
			auto adj = top->adjacency[top->node];
			top->adjacency.erase(top->node);
			for (auto& key : adj)
			{
				Graph* graph = new Graph(*top);
				graph->node = key.first;
				graph->distance = top->distance + key.second;
				graphs.push(graph);
			}
		}
		//delete top;
	}
	/*while (iniGraph.keys != allKeys)
	{
		iniGraph.unlock();
		size_t mindist = INT_MAX;
		const Node* minnode = 0;
		for (auto& key : iniGraph.adjacency[iniGraph.node])
		{
			if (mindist > key.second) {
				mindist = key.second;
				minnode = &key.first;
			}
		}
		//iniGraph.node = minnode ? *minnode : iniGraph.node;
		if (minnode) {
			iniGraph.distance += mindist;
			iniGraph.node = *minnode;
		}
	}
	cout << iniGraph.distance;*/
}
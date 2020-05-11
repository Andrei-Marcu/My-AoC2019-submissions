#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>

#define size 5
#define BUG '#'

using namespace std;

ifstream fin("input.txt");

typedef pair<int, int> coord;

coord directions[] = {
	{-1,0},
	{0,1},
	{1,0},
	{0,-1}
};

inline bool checkBounds(int x) {
	return x < size && x >= 0;
}

struct bugs
{
	size_t biodiv = 0;

	const bool operator[](coord pos) const {
		if (checkBounds(pos.first) && checkBounds(pos.second))
		{
			return biodiv & (1 << (size * pos.first) << pos.second);
		}
		return 0;
	}

	void set(coord pos) {
		biodiv |= 1u << (size * pos.first) << pos.second;
	}

	const bool operator<(const bugs& rhs) const {
		return biodiv < rhs.biodiv;
	}
};

coord operator+(coord &lhs, coord &rhs) {
	return { lhs.first + rhs.first,lhs.second + rhs.second };
}

int main() {
	char c;
	bugs area;
	set<bugs> states;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			fin >> c;
			if (c == BUG) {
				area.set({ i,j });
			}
		}
	}
	states.insert(area);
	while (true)
	{
		bugs tick;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				size_t neighbors = 0;
				coord pos = { i,j };
				for (auto& dir : directions)
				{
					neighbors += area[pos + dir];
				}
				if(neighbors == 1 || (neighbors == 2 && !area[pos]))
				{
					tick.set(pos);
				}
			}
		}
		if (states.find(tick) != states.end()) {
			cout << tick.biodiv;
			break;
		}
		area = tick;
		states.insert(area);
	}
}
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>
#include <bitset>

#define BUG '#'

using namespace std;

ifstream fin("input.txt");

typedef pair<int, int> coord;

const coord directions[] = {
	{-1,0},	//0 up
	{0,1},	//1 down
	{1,0},	//2	left
	{0,-1}	//3	right
};

inline bool checkBounds(int x) {
	return x < 5 && x >= 0;
}

bool checkBounds(coord x) {
	return checkBounds(x.first) && checkBounds(x.second);
}

coord operator+(const coord& lhs, const coord& rhs) {
	return { lhs.first + rhs.first,lhs.second + rhs.second };
}


//At first glance you would think that this spaghetti code hell took hours to debug, but it didnt! 
//Not because it would have been easy to debug, but because it worked on the first try. This and part one too, ROFL.
struct level
{
	bitset<24> cells;
	level * above, * below;

	const coord center = { 3,3 };

	level() {
		above = 0;
		below = 0;
	}

	level(level* creator, bool aboveCreator) {
		if (aboveCreator)
		{
			above = 0;
			below = creator;
		}
		else
		{
			above = creator;
			below = 0;
		}
	}
	
	void createUp() {
		above = new level(this, true);
	}

	void createDown() {
		below = new level(this, false);
	}

	auto operator[](const coord& pos) {
		if (pos == center) {
			throw;
		}
		int i = pos.first * 5 + pos.second;
		i -= i > 12;
		return cells[i];
	}

	size_t getDownNeighbors(size_t dir) {
		if (!below) {
			return 0;
		}
		//the microoptimisation is big with this one!
		int i,
			j = (dir % 2) ? 0 : 4, // true: dir is down/right so we must check up/left
			* a, * b;
		if (dir / 2) {	//true:dir is on horizontal axis
			a = &i;
			b = &j;
		}
		else {			//false: dir is on vertical axis
			a = &j;
			b = &j;
		}
		size_t neighbors = 0;
		for (i = 0; i < 5; i++)
		{
			neighbors += (*below)[{*a, * b}];
		}
		return neighbors;
	}

	void tick(bool up, bool down) {
		if (!above) {
			for (int i = 0; i < 5; i++)
			{
				if ((*this)[{ 0,i }] || (*this)[{ 4,i }]) {
					createUp();
					goto done;
				}
			}
			for (int j = 1; j < 4; j++)
			{
				if ((*this)[{ j,0 }] || (*this)[{ j,4 }]) {
					createUp();
					break;
				}
			}
		}

		done:
		level nextcells;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				coord pos = { i,j };
				if (pos == center)
				{
					if (!below) {
						for (auto& dir : directions)
						{
							if ((*this)[pos + dir]) {
								createDown();
								break;
							}
						}
					}
					continue;
				}

				size_t neighbors = 0;

				for (size_t dir = 0; dir < 4; dir++)
				{
					auto checkpos = pos + directions[dir];
					if (!checkBounds(checkpos)) {
						neighbors += above ? (*above)[center + directions[dir]] : 0;
					}
					else if (checkpos == center) {
						neighbors += getDownNeighbors(dir);
					}
					else
					{
						neighbors += (*this)[checkpos];
					}
				}
				if (neighbors == 1 || (neighbors == 2 && !(*this)[pos]))
				{
					nextcells[pos] = true;
				}
			}
		}

		if (up && above)
			above->tick(true, false);
		if (down && below)
			below->tick(false, true);
		cells = nextcells.cells;
	}

	void tick() {
		tick(true, true);
	}

	size_t count(bool up) {
		auto nr = cells.count();
		if (up) {
			if (above) {
				nr += above->count(true);
			}
		}
		else
		{
			if (below) {
				nr += below->count(false);
			}
		}
		return nr;
	}

	auto count() {
		return count(true) + below ? below->count(false) : 0;
	}
};


int main() {
	char c;
	level area;

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 5; j++)
		{
			fin >> c;
			if (c == BUG) {
				area[{ i,j }] = true;
			}
		}
	}
	
	for (size_t i = 0; i < 200; i++)
	{
		area.tick();
	}
	cout << area.count();
}
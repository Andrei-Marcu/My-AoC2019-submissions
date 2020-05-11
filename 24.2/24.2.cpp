#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>
#include <bitset>

#define BUG '#'
#define MTY '.'

using namespace std;

ifstream fin("input.txt");

typedef pair<int, int> coord;

const coord directions[] = {
	{-1,0},		//0 up
	{1, 0},		//1 down
	{0, -1},	//2	left
	{0, 1}		//3	right
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


//This code used to be broken but still worked for my input somehow, lol
struct level
{
	bitset<24> cells;
	level* above, * below;

	const coord center = { 2,2 };

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
		if (i > 12) i--;
		return cells[i];
	}

	//get neighbors from the lower level given the direction of the cell that is checking from the upper level
	size_t getDownNeighbors(size_t dir) {
		if (!below) {
			return 0;
		}

		//the microoptimisation is big with this one!
		int i,
			j = (dir % 2) ? 0 : 4, // true: dir is down/right so we must check up/left, false: vice-versa
			* a, * b;

		//I'm using pointers so I can easily flip diagonally
		if (dir / 2) {	//true:dir is on horizontal axis
			a = &i;
			b = &j;
		}
		else {			//false: dir is on vertical axis
			a = &j;
			b = &i;
		}

		size_t neighbors = 0;
		//now I can cover all cases with just one for! Nice!
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
				if ((*this)[{ 0, i }] || (*this)[{ 4, i }]) {
					createUp();
					goto done;
				}
			}
			for (int j = 1; j < 4; j++)
			{
				if ((*this)[{ j, 0 }] || (*this)[{ j, 4 }]) {
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
		return count(true) + (below ? below->count(false) : 0);
	}

	void print() {
		/*for (size_t i = 0; i < 12; i++)
		{
			if (i % 5 == 0)
				cout << endl;
			cout << (cells[i] ? BUG : MTY);
		}
		cout << ' ';
		for (size_t i = 12; i < 24; i++)
		{
			if (i % 5 == 4)
				cout << endl;
			cout << (cells[i] ? BUG : MTY);
		}*/
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				coord pos = { i,j };
				if (pos == center) {
					cout << ' ';
				}
				else {
					cout << (operator[](pos) ? BUG : MTY);
				}
			}
			cout << endl;
		}
	}

	void printall() {
		int lvl = 0;
		level* ptr = this;
		while (ptr->below)
		{
			ptr = ptr->below;
			lvl--;
		}
		for (; ptr ; ptr = ptr->above, lvl++ )
		{
			cout << "Depth " << lvl << ":\n";
			ptr->print();
		}
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
				area[{ i, j }] = true;
			}
		}
	}
	//area.printall();

	for (size_t i = 0; i < 200; i++)
	{
		area.tick();
		/*cout << "\nMin " << i + 1 << ":\n";
		area.printall();
		cout << area.count();
		cin.get();*/

	}
	cout << area.count();
}
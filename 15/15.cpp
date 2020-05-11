#include <iostream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <algorithm>

#define limit 10000

using namespace std;

typedef long long number;
typedef pair<int, int> coord;

ifstream fin("input.txt");

number s[limit], i, base;

int direction, output, mini, minj, maxi, maxj;

map<coord, int> ship;

coord pos, iniPos, sysPos, directions[5] = {
	{0,0},
	{-1,0},//[1]north
	{1,0},//[2]south
	{0,-1},//[3]west
	{0,1}//[4]east
};

coord operator+=(coord& lhs, int dir) {
	auto& rhs = directions[dir];
	lhs.first += rhs.first;
	lhs.second += rhs.second;
	return lhs;
}

coord operator+(coord& lhs, int dir) {
	auto& rhs = directions[dir];
	return { lhs.first + rhs.first, lhs.second + rhs.second };
}

int reverse(int dir) {
	if (!dir)
		return 0;
	return dir + (dir % 2 ? 1 : -1);
}

int peek(coord coordinate) {
	auto query = ship.find(coordinate);
	if (query == ship.end())
	{
		return -1;
	}
	return query->second;
}

//first parameter(excluding the opcode) is 1
number& getval(int parameter) {
	switch (s[i] / (number)pow(10ll, parameter + 1ll) % 10)
	{
	case 2:
		return s[base + s[i + parameter]];
	case 1:
		return s[i + parameter];
	case 0:
		return s[s[i + parameter]];
	}
	cout << "Argh!";
	return s[0];
}

bool cycle() {
	switch (s[i] % 100)
	{
	case 1: {
		getval(3) = getval(1) + getval(2);
		i += 4;
		break;
	}
	case 2: {
		getval(3) = getval(1) * getval(2);
		i += 4;
		break;
	}
	case 3: {
		getval(1) = direction;
		i += 2;
		break;
	}
	case 4: {
		//cout << getval(1) << ' ';
		output = getval(1);
		ship[pos + direction] = output;
		if (output) {
			pos += direction;
			mini = min(pos.first, mini);
			minj = min(pos.second, minj);
			maxi = max(pos.first, maxi);
			maxj = max(pos.second, maxj);
			if (output == 2) {
				sysPos = pos;
			}
		}
		i += 2;
		return 0;
	}
	case 5: {
		if (getval(1) != 0) {
			i = getval(2);
		}
		else
		{
			i += 3;
		}
		break;
	}
	case 6: {
		if (getval(1) == 0) {
			i = getval(2);
		}
		else
		{
			i += 3;
		}
		break;
	}
	case 7: {
		getval(3) = getval(1) < getval(2);
		i += 4;
		break;
	}
	case 8: {
		getval(3) = getval(1) == getval(2);
		i += 4;
		break;
	}
	case 9: {
		base += getval(1);
		i += 2;
		break;
	}
	case 99:
		return 0;
	default:
		cout << "Oh no!";
	}
	return 1;
}

int step(int dir) {
	if (!dir) {
		return ship[iniPos];
	}
	direction = dir;
	while (cycle());
	return output;
}

//as long as the ship is an acyclic maze(studied the result) a DFS algorithm will guarantee the shortest path
//meanwhile I was looking to implement A*, foolish me
void search(int dir, int depth) {
	int res = step(dir);
	if (res) {
		for (int i = 1; i <= 4; i++)
		{
			if (peek(pos + i) == -1) {
				search(i, depth + 1);
			}
		}
		step(reverse(dir));
		if (res == 2) {
			cout << depth << '\n';
		}
	}
}

int spread(coord pos, int depth) {
	if (ship[pos]) {
		ship[pos] = 0;
		int maxdepth = depth;
		for (size_t i = 1; i <= 4; i++)
		{
			maxdepth = max(spread(pos + i, depth + 1), maxdepth);
		}
		return maxdepth;
	}
	return 0;
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	i = 0;
	//inipos = 
	//pos = inipos;
	ship[iniPos] = 1;
	search(0, 0);

	for (int i = mini - 1; i <= maxi + 1; i++)
	{
		for (int j = minj - 1; j <= maxj + 1; j++)
		{
			if (!i & !j) {
				cout << 'X';
			}
			else
			{
				switch (peek({ i, j }))
				{
				case 1:
					cout << ' ';
					break;
				case 2:
					cout << 'O';
					break;
				default:
				case -1:
					cout << '#';
					break;
				}
			}
		}
		cout << '\n';
	}

	cout << spread(sysPos, 0);
}
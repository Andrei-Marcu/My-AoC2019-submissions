#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <map>;

#define limit 10000

using namespace std;

typedef long long number;

typedef pair<int, int> coord;

ifstream fin("input.txt");

number s[limit], p[limit], i, base;

vector<vector<char>> camera;

map<coord, bool> ship;

bool part1 = 1;

char dump;

coord pos, rotations[4] = {
	{-1,0},	//^
	{0,1},	//>
	{1,0},	//V
	{0,-1}	//<
};

int rotation;

coord& operator+=(coord& lhs, int rhs) {
	lhs.first += rotations[rhs].first;
	lhs.second += rotations[rhs].second;
	return lhs;
}

coord operator+(coord& lhs, int rhs) {
	return { lhs.first + rotations[rhs].first,
		lhs.second + rotations[rhs].second };
}

int getRotation(int c) {
	switch (c) {
	case '^':
		return 0;
	case '>':
		return 1;
	case 'v':
		return 2;
	case '<':
		return 3;
	}
	return -1;
}

inline bool isScaffold(char c) {
	switch (c)
	{
	case '#':
	case '^':
	case '<':
	case '>':
	case 'v':
		return 1;
	default:
		return 0;
	}
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
		fin.get(dump);
		cout << dump;
		getval(1) = dump;
		i += 2;
		break;
	}
	case 4: {
		int output = getval(1);
		if (output > 255) {
			cout << output;
		}
		else
			cout << (char)output;
		if (part1) {
			if (output == '\n') {
				camera.emplace_back();
			}
			else
			{
				if (isScaffold(output))
				{
					coord loc = { camera.size() - 1,camera.back().size() };
					ship[loc] = 1;
					if (getRotation(output) >= 0) {
						rotation = getRotation(output);
						pos = loc;
					}
				}
				camera.back().push_back(output);
			}
		}
		i += 2;
		break;
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

int getRight(int rot) {
	return (rot + 1) % 4;
}

int getLeft(int rot) {
	rot--;
	if (rot == -1)
	{
		rot = 3;
	}
	return rot;
}

bool isIntersection(int i, int j) {
	return isScaffold(camera[i][j]) &&
		isScaffold(camera[i - 1][j]) &&
		isScaffold(camera[i + 1][j]) &&
		isScaffold(camera[i][j - 1]) &&
		isScaffold(camera[i][j + 1]);
}

int main() {
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	i = 0;
	memcpy(p, s, sizeof(number) * limit);
	camera.emplace_back();
	while (cycle());

	while (!camera.back().size())
	{
		camera.pop_back();
	}

	size_t sum = 0, iLim = camera.size() - 1, jLim = camera.front().size() - 1;
	for (size_t i = 1; i < iLim; i++)
	{
		for (size_t j = 1; j < jLim; j++)
		{
			if (isIntersection(i, j)) {
				sum += i * j;
			}
		}
	}
	cout << sum << "\n\n";
	memcpy(s, p, sizeof(number) * limit);
	s[0] = 2LL;
	while (true)
	{
		for (i = 0; ship[pos + rotation]; i++) {
			pos += rotation;
		}
		if (i) {
			cout << i << ',';
		}
		if (ship[pos + getRight(rotation)]) {
			cout << "R,";
			rotation = getRight(rotation);
		}
		else if (ship[pos + getLeft(rotation)]) {
			cout << "L,";
			rotation = getLeft(rotation);
		}
		else
		{
			break;
		}
	}
	fin.close();
	part1 = 0;
	cout << "\n\nSince this year I've been focused on solving ASAP, this is not automatic."
		<< "\nYou need to find the patterns by yourself(which is faster than me coding an automation)"
		<< "\nand load them into an input2.txt file which is going to be parsed character by character,"
		<< "\nincluding new lines. See input2.ex which is made after the example\nPress RETURN when ready...";
	cin.get();
	fin = ifstream("input2.txt");
	i = 0;
	while (cycle());
}
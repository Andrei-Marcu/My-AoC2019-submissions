#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <map>
#include <algorithm>

#define limit 10000

using namespace std;

typedef long long number;
typedef pair<int, int> pixel;

ifstream fin("input.txt");

void add(pixel& p1, pixel& p2) {
	p1.first += p2.first;
	p1.second += p2.second;
}

number s[limit], i, base;

pixel pos;
map<pixel, bool> color;

pixel direction[4] = {	
						{-1, 0 },
						{ 0, 1 },
						{ 1, 0 },
						{ 0, -1} 
					 };

int dirptr;

bool state;

void turn(bool right) {
	if (right) {
		dirptr = (dirptr + 1) % 4;
	}
	else
	{
		dirptr--;
		if (dirptr == -1) dirptr = 3;
	}
}

pixel& getDir() {
	return direction[dirptr];
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
		getval(1) = color[pos];
		i += 2;
		break;
	}
	case 4: {
		//cout << getval(1) << ' ';
		if (state)
		{
			turn(getval(1));
			add(pos, getDir());
		}
		else
		{
			color[pos] = getval(1);
		}
		state = !state;
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

void day1() {
	while (cycle());
	cout << color.size();
}

void day2() {
	color[pos] = 1;
	while (cycle());
	int mini = INT_MAX, maxi = INT_MIN, minj = INT_MAX, maxj = INT_MIN;

	for (auto& el : color)
	{
		auto i = el.first.first;
		auto j = el.first.second;
		mini = min(mini, i);
		minj = min(minj, j);
		maxi = max(maxi, i);
		maxj = max(maxj, j);
	}

	for (int i = mini; i <= maxi; i++)
	{
		for (int j = minj; j < maxj; j++)
		{
			if (color[{i, j}]) {
				cout << '#';
			}
			else
			{
				cout << '.';
			}
		}
		cout << '\n';
	}
}

int main() {
	direction[0] = {-1,  0};
	direction[1] = { 0,  1};
	direction[2] = { 1,  0};
	direction[3] = { 0, -1};

	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	i = 0;

	day2();

	return 0;
}
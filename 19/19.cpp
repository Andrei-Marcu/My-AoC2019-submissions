#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define limit 1000
#define GRID 50
#define SQR 100
#define EDGE 10

using namespace std;

typedef long long number;

ifstream fin("input.txt");

number s[limit], p[limit], i, base, x, y, n;

bool state = 1, isPulld;

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
		//cin >> getval(1);
		getval(1) = state ? x : y;
		state = !state;
		i += 2;
		break;
	}
	case 4: {
		isPulld = getval(1);
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

bool check(int j, int k) {
	x = j;
	y = k;
	i = 0;
	base = 0;
	memcpy(s, p, n);
	while (cycle());
	return isPulld;
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	n = sizeof(number) * limit;//i;

	memcpy(p, s, n);

	int sum = 0;
	for (size_t j = 0; j < GRID; j++)
	{
		for (size_t k = 0; k < GRID; k++)
		{
			sum += check(j, k);
			//cout << (check(j, k) ? '#' : '.');
		}
		//cout << '\n';
	}
	int x = 99, y = 0;
	while (!check(x,y))
	{
		y++;
	}
	while (!check(x-99,y+99))
	{
		if (check(x + 1, y)) {
			x++;
		}
		else
		{
			y++;
		}
	}
	cout << sum << ' ' << (x-99) * 10000 + y;
}
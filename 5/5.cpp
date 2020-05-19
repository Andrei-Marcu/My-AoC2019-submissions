#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define limit 10000

using namespace std;

ifstream fin("input.txt");

int s[limit], p[limit], i, input, x;

int getval(int parameter) {
	if (s[i] / 100 / (int)pow(10, parameter - 1) % 10) {
		return s[i + parameter];
	}
	return s[s[i + parameter]];
}

bool execute() {
	switch (s[i] % 100)
	{
	case 1: {
		s[s[i + 3]] = getval(1) + getval(2);
		i += 4;
		break;
	}
	case 2: {
		s[s[i + 3]] = getval(1) * getval(2);
		i += 4;
		break;
	}
	case 3: {
		//cin >> s[s[i + 1]];
		s[s[i + 1]] = input;
		i += 2;
		break;
	}
	case 4: {
		cout << getval(1) << ' ';
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
		s[s[i + 3]] = getval(1) < getval(2);
		i += 4;
		break;
	}
	case 8: {
		s[s[i + 3]] = getval(1) == getval(2);
		i += 4;
		break;
	}
	case 99:
		return 0;
	default:
		cout << "Oh no";
	}
	return 1;
}

void go(int in) {
	input = in;
	i = 0;
	while (execute());
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	x = sizeof(int) * i;
	memcpy(p, s, x);
	go(1);
	memcpy(s, p, x);
	go(5);
}
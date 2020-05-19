#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define limit 10000

using namespace std;

typedef long long number;

ifstream fin("input.txt");

number s[limit], p[limit], i, base, x, input;

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
		getval(1) = input;
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

void go(number in) {
	input = in;
	i = 0;
	base = 0;
	while (cycle());
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	x = i * sizeof(number);
	memcpy(p, s, x);
	go(1);
	memcpy(s, p, x);
	go(2);
}
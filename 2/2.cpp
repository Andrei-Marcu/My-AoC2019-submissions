#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

ifstream fin("input.txt");

int s[2000], p[2000], x, i;

bool execute() {
	if (s[i] == 1)
		s[s[i + 3]] = s[s[i + 1]] + s[s[i + 2]];
	else if (s[i] == 2)
		s[s[i + 3]] = s[s[i + 1]] * s[s[i + 2]];
	else
		return 0;
	i += 4;
	return 1;
}

void part1() {
	i = 0;
	while (execute());
	cout << s[0];
}

void part2() {
	int x = sizeof(int) * i;
	memcpy(p, s, x);
	for (size_t j = 0; j < 100; j++)
	{
		for (size_t k = 0; k < 100; k++)
		{
			s[1] = j;
			s[2] = k;
			i = 0;
			while (execute());
			if (s[0] == 19690720) {
				cout << (j * 100 + k);
				return;
			}
			memcpy(s, p, x);
		}
	}
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	part1();
}
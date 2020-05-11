#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

ifstream fin("input.txt");

//part 1
inline bool check1(int nr) {
	int lastdigit = 10;
	bool doubled = 0;
	while (nr > 0)
	{
		if (nr % 10 > lastdigit) {
			return 0;
		}
		if (nr % 10 == lastdigit)
		{
			doubled = 1;
		}
		lastdigit = nr % 10;
		nr /= 10;
	}
	return doubled;
}

//part2
inline bool check2(int nr) {
	int lastdigit = 10;
	bool doubled = 0;
	while (nr > 0)
	{
		if (nr % 10 > lastdigit) {
			return 0;
		}
		if ((nr % 100) % 11 == 0)
		{
			if ((nr % 1000) % 111 != 0) {
				doubled = 1;
				nr /= 10;
			}
			else {
				while ((nr % 100) % 11 == 0)
				{
					nr /= 10;
				}
			}
		}
		lastdigit = nr % 10;
		nr /= 10;
	}
		return doubled;
}

int main() {
	int x1, x2, s = 0;
	char dump;
	fin >> x1 >> dump >> x2;
	for (int i = x1 + 1; i < x2; i++)
	{
		s += check1(i);
	}
	cout << s;
}
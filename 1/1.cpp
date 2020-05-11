#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

ifstream fin("input.txt");

long long s1, s2, x;
int main() {
	while (fin >> x)
	{
		x = x / 3 - 2;
		s1 += x;
		while ((x = x / 3 - 2)>0)
		{
			s2 += x;
		}
	}
	cout << s1 << ' ' << s1 + s2;
}
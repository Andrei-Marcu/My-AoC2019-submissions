#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define limit 100

using namespace std;

typedef long long number;

ifstream fin("input.txt");
ofstream fout("output.txt");

number x, i;

//for the record, this program has been made after my day 25 part 1 submission, so I did not use it to attempt cheating, I was just curious to see afterwards
//is it supposed to find strings in code, but I didn't find anything, I guess it's encoded or something.
int main() {
	char dump;
	for (i = 1; fin >> x; i++) {
		x %= 256;
		if (x == 10) {
			fout << endl;
		}
		else if (x > -1 && isprint(x))
		{
			fout << (char)x;
		}
		fin.get(dump);
		/*if (!(i % limit))
			fout << endl;*/
	}
	i = 0;
}
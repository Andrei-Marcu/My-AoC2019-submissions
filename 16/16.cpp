#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define LIMIT 10000000
#define REPEAT 10000

typedef int number;

number a[LIMIT], b[LIMIT], * s = a, * p = b;
char x;
int n, offset;

ifstream fin("input.txt");

//inb4 browsing Reddit and realizing this could have been solved using partial sums. HOW I DID NOT THINK OF IT! This day is far from optimal

void part1() {
	offset = 0;
	for (size_t phase = 0; phase < 100; phase++)
	{
		for (size_t i = offset; i < n; i++)
		{
			bool state = 1;
			p[i] = 0;
			for (size_t j = i; j < n; j += (i + 1) * 2)
			{
				for (size_t k = 0; k <= i && j + k < n; k++)
				{
					if (state) {
						p[i] += s[j + k];
					}
					else
					{
						p[i] -= s[j + k];
					}
				}
				state = !state;
			}
			p[i] = abs(p[i]) % 10;
		}
		swap(s, p);
	}
}

void part2() {
	for (size_t i = n; i < n * REPEAT; i++)
	{
		s[i] = s[i - n];
	}
	n *= REPEAT;
	offset = 0;
	for (size_t i = 0; i < 7; i++)
	{
		offset = offset * 10 + s[i];
	}
	for (size_t phase = 0; phase < 100; phase++)
	{
		//quite upset of the way I had to solve this day. I had to rely on the fact that the first digits point at least at half the input.
		if (offset >= n / 2)
		{
			int sum = 0;
			for (size_t i = n - 1; i >= offset; i--)
			{
				sum += s[i];
				p[i] = sum;
			}
			for (size_t i = offset; i < n; i++)
			{
				p[i] = abs(p[i]) % 10;
			}
		}
		//here's the code that should work universally, estimate of 10 hours to solve actual inputs
		else
		{
			for (size_t i = offset; i < n; i++)
			{
				bool state = 1;
				p[i] = 0;
				for (size_t j = i; j < n; j += (i + 1) * 2)
				{
					for (size_t k = 0; k <= i && j + k < n; k++)
					{
						if (state) {
							p[i] += s[j + k];
						}
						else
						{
							p[i] -= s[j + k];
						}
					}
					state = !state;
				}
				p[i] = abs(p[i]) % 10;
			}
		}
		swap(s, p);
	}
}

int main() {
	fin >> x;
	do {
		s[n] = x - '0';
		n++;
	} while (fin >> x);

	//select part here:
	part2();
	for (size_t i = offset; i < offset + 8; i++)
	{
		number test = a[i];
		cout << test;
	}
}
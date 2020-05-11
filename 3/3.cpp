#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <utility>

#define middle 10001
#define limit 20001

using namespace std;

//separate input file for each wire, replace commas with spaces beforehand
ifstream fin("input.txt");
ifstream fin2("input2.txt");

unsigned short a[limit][limit];

struct point {
	int v, h;
	point(int v, int h) : v(v), h(h) {}
	auto operator+=(point& rhs) {
		v += rhs.v;
		h += rhs.h;
		//return point(v + rhs.v, h + rhs.h);
	}
	auto operator*(int& rhs) {
		return point(v * rhs, h * rhs);
	}
	int dist() {
		return abs(v - middle) + abs(h - middle);
	}
};

auto center = point(middle, middle), loc = center;

point* p[256];
unsigned short travel;

int main() {
	int min = INT_MAX;
	int mindist = INT_MAX;
	p['L'] = new point(0, -1);
	p['R'] = new point(0, 1);
	p['U'] = new point(-1, 0);
	p['D'] = new point(1, 0);

	//I know I'm not using string, but I knew how to parse quickly with a char array and I was pressured by time
	char s[10];
	while (fin >> s)
	{
		auto& dir = *p[s[0]];
		auto length = atoi(s + 1);
		for (size_t i = 0; i < length; i++)
		{
			loc += dir;
			a[loc.v][loc.h] = ++travel;
		}
	}

	loc = center;
	travel = 0;
	while (fin2 >> s)
	{
		auto& dir = *p[s[0]];
		auto length = atoi(s + 1);
		for (size_t i = 0; i < length; i++)
		{
			travel++;
			loc += dir;
			if (a[loc.v][loc.h]) {
				if (loc.dist() < min) min = loc.dist();
				if (a[loc.v][loc.h] + travel < mindist) mindist = a[loc.v][loc.h] + travel;
			}
		}
	}
	cout << min << ' ' << mindist;
}


#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef pair<int, int> Angle;

ifstream fin("input.txt");

struct Coord {
	int x, y, pos;
	Angle angle;
	Coord() {}
	Coord(int x, int y) : x(x), y(y) {}
	Coord& operator-(Coord& rhs) {
		return *new Coord(x - rhs.x, y - rhs.y);
	}
	int distSqr() {
		return x * x + y * y;
	}
	void gcd() {
		if (!x)
		{
			if (!y)
				return;
			y /= abs(y);
			return;
		}
		if (!y) {
			x /= abs(x);
			return;
		}
		int a = abs(x), b = abs(y), r = a % b;
		while (r)
		{
			a = b;
			b = r;
			r = a % b;
		}
		x /= b;
		y /= b;
	}
	Coord& operator/=(Coord& rhs) {
		auto& rez = *this - rhs;
		rez.gcd();
		angle.first = rez.x;
		angle.second = rez.y;
		return *this;
	}
	double getAbsAngle() {
		auto& x = angle.first;
		auto& y = angle.second;
		if (x == 0 && y == 0) {
			pos = INT_MAX;
			return 4.0;
		}
		if (x == 0 && y == -1)
			return -4.0;
		return atan2(-x, y);
	}
	bool operator<(Coord& rhs) {
		double thisAngle = getAbsAngle();
		double rhsAngle = rhs.getAbsAngle();
		if (this->pos == rhs.pos) {
			return thisAngle < rhsAngle;
		}
		return this->pos < rhs.pos;
	}
}best1;

bool lessDist(Coord* c1, Coord* c2) {
	return (*c1 - best1).distSqr() < (*c2 - best1).distSqr();
}

double getAbsAngl(int x, int y) {
	if (x == 0 && y == 0) {
		return 4.0;
	}
	if (x == 0 && y == -1)
		return -4.0;
	return atan2(-x, y);
}

int main() {
	char s[200];
	vector<Coord> asteroids;
	for (size_t y = 0; fin >> s; y++)
	{
		for (size_t x = 0; s[x]; x++)
		{
			if (s[x] == '#') {
				asteroids.emplace_back(x, y);
			}
		}
	}
	size_t mx = 0;
	for (auto& asteroid : asteroids)
	{
		set<Angle> angles;
		for (auto& comp : asteroids)
		{
			comp /= asteroid;
			angles.insert(comp.angle);
		}
		if (mx < angles.size()) {
			mx = angles.size();
			best1 = asteroid;
		}
	}
	cout /*<< best1.x << ' ' << best1.y << '\n'*/ << mx - 1;

	map<Angle,vector<Coord*>> astMap;
	for (auto& asteroid : asteroids)
	{
		asteroid /= best1;
		astMap[asteroid.angle].push_back(&asteroid);
	}
	for (auto& elem : astMap)
	{
		auto& vec = elem.second;
		sort(vec.begin(), vec.end(), lessDist);
		for (size_t i = 0; i < vec.size(); i++)
		{
			vec[i]->pos = i;
		}
	}
	sort(asteroids.begin(), asteroids.end());
	cout << ' ' << (asteroids[199].x * 100 + asteroids[199].y);
}
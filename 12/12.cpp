#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>
#include <stack>
#include <algorithm>

# define N 4

using namespace std;
typedef long long big;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct MoonCoord {
	big pos, vel = 0;

	MoonCoord() {}

	void updatePos() {
		pos += vel;
	}
	void changeVel(MoonCoord& rhs) {
		if (pos < rhs.pos) {
			vel++;
		}
		else if (pos > rhs.pos)
		{
			vel--;
		}
	}

	bool operator==(const MoonCoord& rhs) const {
		return pos == rhs.pos && vel == rhs.vel;
	}

	bool operator<(const MoonCoord& rhs) const {
		if (pos == rhs.pos)
			return vel < rhs.vel;
		return pos < rhs.pos;
	}

	bool operator!() {
		return vel == 0;
	}
};

MoonCoord moons[3][N];
big init[3][N];

bool isBack(int i) {
	for (size_t j = 0; j < N; j++)
	{
		if (moons[i][j].vel != 0 || moons[i][j].pos != init[i][j])
			return false;
	}
	return true;
}

big day1() {
	for (size_t i = 0; i < 3; i++)
	{
		auto& axis = moons[i];
		for (size_t k = 0; k < 1000; k++)
		{
			for (auto& coord : axis)
			{
				for (auto& coord2 : axis)
				{
					coord.changeVel(coord2);
				}
			}
			for (auto& coord : axis)
			{
				coord.updatePos();
			}
		}
	}

	big sol = 0;

	for (size_t i = 0; i < N; i++)
	{
		sol += (abs(moons[0][i].pos) + abs(moons[1][i].pos) + abs(moons[2][i].pos)) * (abs(moons[0][i].vel) + abs(moons[1][i].vel) + abs(moons[2][i].vel));
	}
	return sol;
}

big day2() {
	unsigned long long result = 1;

	for (size_t i = 0; i < 3; i++)
	{
		auto& axis = moons[i];
		//while (search(axis[j]).second)
		big k;
		for (k = 1; true; k++)
		{
			for (auto& coord : axis)
			{
				for (auto& coord2 : axis)
				{
					coord.changeVel(coord2);
				}
			}
			for (auto& coord : axis)
			{
				coord.updatePos();
			}
			if (isBack(i)) break;
		}
		unsigned long long a = k, b = result, r = a % b;
		while (r)
		{
			a = b;
			b = r;
			r = a % b;
		}
		result *= k / b;
	}

	return result;
}

int main() {

	int intersect[3 * N];

	for (size_t i = 0; i < N; i++)
	{
		fin >> moons[0][i].pos >> moons[1][i].pos >> moons[2][i].pos;
	}
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			init[i][j] = moons[i][j].pos;
		}
	}
	cout << day1();
}
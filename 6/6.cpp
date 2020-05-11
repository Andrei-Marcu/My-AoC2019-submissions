#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>
#include <map>

using namespace std;

//replace ) with space
ifstream fin("input.txt");

map<string, set<string>> sons;
map<string, string> father;
map<string, int> level;

int calculate_orbits(string center, int indirect_orbits) {
	int sum = indirect_orbits;
	level[center] = indirect_orbits;
	for (auto& orbit : sons[center])
	{
		sum += calculate_orbits(orbit, indirect_orbits + 1);
	}
	return sum;
}

int main() {
	string center, orbit;
	while (fin >> center)
	{
		fin >> orbit;
		sons[center].emplace(orbit);
		father.emplace(orbit, center);
	}
	cout << calculate_orbits("COM", 0);

	//to make matters much easier I'm just gonna pretend that Santa can also travel and they can only travel up untill they meet
	int transfers = 0;
	string you = "YOU", santa = "SAN";

	while (level[you] < level[santa])
	{
		santa = father[santa];
		transfers++;
	}
	while (level[you] > level[santa])
	{
		you = father[you];
		transfers++;
	}
	while (father[you] != father[santa])
	{
		you = father[you];
		santa = father[santa];
		transfers += 2;
	}
	cout << ' ' << transfers;
}
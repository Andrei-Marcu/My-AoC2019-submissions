#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <utility>
#include <vector>

#define ORES 1000000000000u

using namespace std;
typedef unsigned long long big;

//replace commas and "=>" with nothing
ifstream fin("input.txt");
ofstream fout("output.txt");

string ORE = "ORE";
string FUEL = "FUEL";

big oreConsumed;

struct Recipe;

map<string, Recipe> materials;

inline big ceilDivision(big divident, int divisor) {
	return divident / divisor + (bool)(divident % divisor);
}

struct Recipe {
	int result;
	big stock = 0;
	string material;
	vector<pair<string, int>> ingredients;

	void craft(big amount) {
		big reactions = ceilDivision(amount, result);
		for (auto& ingredient : ingredients)
		{
			big quantity = reactions * ingredient.second;
			if (ingredient.first == ORE) {
				oreConsumed += quantity;
			}
			else
			{
				auto& recipe = materials[ingredient.first];
				if (recipe.stock < quantity)
				{
					recipe.craft(quantity - recipe.stock);
				}
				recipe.stock -= quantity;
			}
		}
		stock += reactions * result;
	}
};

int main() {
	//input
	int x;
	string mat;
	Recipe recipe;

	while (fin >> x)
	{
		fin >> mat;
		if (fin.peek() <= '\n') {
			recipe.result = x;
			recipe.material = mat;
			materials.insert({ mat, Recipe(recipe) });
			recipe = Recipe();
		}
		else
		{
			recipe.ingredients.emplace_back(mat, x);
		}
	}

	auto& fuel = materials[FUEL];
	big quantity = 1;
	fuel.craft(quantity);
	cout << oreConsumed;

	big plus = ORES / ((double)oreConsumed / quantity) - quantity;
	do {
		fuel.craft(plus);
		quantity += plus;
		plus = ORES / ((double)oreConsumed / quantity) - quantity;
	} while (plus);

	//I suspect that there might be a particular case in which the quantity can exceed by 1
	cout << ' ' << quantity - (ORES < oreConsumed);

	return 0;
}
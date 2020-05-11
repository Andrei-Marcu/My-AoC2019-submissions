#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define W 25
#define H 6

using namespace std;

ifstream fin("input.txt");

//Why? Because I'm limited by the technology of my time, that's why
struct table {
	int content[H][W];
	inline int* operator[](int h) {
		return content[h];
	}
};

vector<table> layers;
int min0s = INT_MAX;
int minpos;

auto chars = " # ";

int main() {
	while (fin.peek() > '\n')
	{
		layers.emplace_back();
		auto& last = layers.back();
		int no0s = 0;
		for (size_t i = 0; i < H; i++)
		{
			for (size_t j = 0; j < W; j++)
			{
				last[i][j] = fin.get() - '0';
				no0s += !last[i][j];
			}
		}
		if (no0s < min0s)
		{
			min0s = no0s;
			minpos = layers.size();
		}
	}
	minpos--;
	int no1 = 0, no2 = 0;
	auto& layer = layers[minpos];
	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			if (layer[i][j] == 1)
				no1++;
			else if (layer[i][j] == 2)
				no2++;
		}
	}
	cout << (no1 * no2) << endl;

	table final;
	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			for (auto& layer : layers)
			{
				final[i][j] = layer[i][j];
				if (layer[i][j] != 2)break;
			}
		}
	}

	for (size_t i = 0; i < H; i++)
	{
		for (size_t j = 0; j < W; j++)
		{
			cout << chars[final[i][j]];
		}
		cout << endl;
	}
}
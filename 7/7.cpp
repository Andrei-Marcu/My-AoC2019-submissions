#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

#define LIMIT 10000
#define NRAMP 5

using namespace std;

ifstream fin("input.txt");

int count, input, phases[NRAMP];
bool isPart2, run;
vector<int> prog;

class Amplifier {
public:
	static void reSet() {
		for (auto& amp : amps)
		{
			amp.mem = prog;
			amp.pc = 0;
			amp.phased = 0;
		};
		input = 0;
		run = 1;
	}

	static void setPhase(int k) {
		for (size_t i = NRAMP; i > 0; i--)
		{
			phases[NRAMP - i] = k % i;
			k /= i;
		}
		bool skip[NRAMP];
		memset(skip, 0, NRAMP);
		for (size_t i = 0; i < NRAMP; i++)
		{
			for (size_t j = 0; j <= phases[i]; j++)
			{
				phases[i] += skip[j];
			}
			skip[phases[i]] = 1;
		}
		if (isPart2) {
			for (auto& phase : phases)
			{
				phase += NRAMP;
			}
		}
	}

	Amplifier() {
		nr = ::count++;
	}

	void execute() {
		while (cycle());
	}

private:
	vector<int> mem;
	int pc = 0;
	bool phased = false;
	int nr;

	int getval(int parameter) {
		if (mem[pc] / 100 / (int)pow(10, parameter - 1) % 10) {
			return mem[pc + parameter];
		}
		return mem[mem[pc + parameter]];
	}

	bool cycle() {
		switch (mem[pc] % 100)
		{
		case 1: {
			mem[mem[pc + 3]] = getval(1) + getval(2);
			pc += 4;
			break;
		}
		case 2: {
			mem[mem[pc + 3]] = getval(1) * getval(2);
			pc += 4;
			break;
		}
		case 3: {
			//cin >> mem[mem[pc + 1]];
			if (phased)
			{
				mem[mem[pc + 1]] = input;
			}
			else
			{
				mem[mem[pc + 1]] = phases[nr];
				phased = 1;
			}
			//cout << 'pc';
			pc += 2;
			break;
		}
		case 4: {
			input = getval(1);
			//if (state) cout << "Oh, come on! ";
			//cout << getval(1) << ' ';
			//cout << 'o';
			pc += 2;
			return 0;
		}
		case 5: {
			if (getval(1) != 0) {
				pc = getval(2);
			}
			else
			{
				pc += 3;
			}
			break;
		}
		case 6: {
			if (getval(1) == 0) {
				pc = getval(2);
			}
			else
			{
				pc += 3;
			}
			break;
		}
		case 7: {
			mem[mem[pc + 3]] = getval(1) < getval(2);
			pc += 4;
			break;
		}
		case 8: {
			mem[mem[pc + 3]] = getval(1) == getval(2);
			pc += 4;
			break;
		}
		case 99: {
			run = 0;
			return 0;
		}
		default:
			cout << "Oh no";
			pc++;
		}
		return 1;
	}
}amps[NRAMP];

void go(bool part2) {
	isPart2 = part2;
	int maxoutput = INT_MIN;
	for (size_t k = 0; k < 120; k++)
	{
		Amplifier::setPhase(k);
		Amplifier::reSet();
		for (size_t j = 0; run; j = (j + 1) % NRAMP)
		{
			amps[j].execute();
		}
		if (input > maxoutput)
		{
			maxoutput = input;
		}
	}
	cout << maxoutput;
}

int main() {
	int x;
	char dump;
	for (int i = 0; fin >> x; i++) {
		prog.push_back(x);
		fin.get(dump);
	}
	go(0);
	cout << ' ';
	go(1);
}
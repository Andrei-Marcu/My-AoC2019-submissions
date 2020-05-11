#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define limit 1000000
#define XLMT 39
#define YLMT 21
using namespace std;

typedef long long number;

ifstream fin("input.txt");

number s[limit], i, base;

int game[YLMT][XLMT], state, x, y, block, score, pad, ball;
string chars = " X#_O";


void draw() {
	//system("CLS");
	for (size_t y = 0; y < YLMT; y++)
	{
		for (size_t x = 0; x < XLMT; x++)
		{
			cout << chars[game[y][x]];
		}
		cout << endl;
	}
}

//first parameter(excluding the opcode) is 1
number& getval(int parameter) {
	switch (s[i] / (number)pow(10ll, parameter + 1ll) % 10)
	{
	case 2:
		return s[base + s[i + parameter]];
	case 1:
		return s[i + parameter];
	case 0:
		return s[s[i + parameter]];
	}
	cout << "Argh!";
	return s[0];
}

bool cycle() {
	switch (s[i] % 100)
	{
	case 1: {
		getval(3) = getval(1) + getval(2);
		i += 4;
		break;
	}
	case 2: {
		getval(3) = getval(1) * getval(2);
		i += 4;
		break;
	}
	case 3: {
		//cin >> getval(1);
		auto& input = getval(1);
		//draw();
		if (pad < ball) {
			input = 1;
		}
		else if (pad > ball)
		{
			input = -1;
		}
		else
		{
			input = 0;
		}
		i += 2;
		break;
	}
	case 4: {
		//cout << getval(1) << ' ';
		number output = getval(1);
		//cout << output << ' ';
		switch (state)
		{
		case 0:
			x = output;
			break;
		case 1:
			y = output;
			break;
		case 2:
			block = output;
			if (x == -1) {
				score = block;
				//cout << endl << score << endl;
				break;
			}
			if (block == 3) {
				pad = x;
			}
			if (block == 4) {
				ball = x;
			}
			game[y][x] = block;
			/*cout << endl;
			if (x >= XLMT || y > YLMT || x < 0 || y < 0)
			{
				cout << "Buff it! " << x << ' ' << y << endl;
			}*/
			break;
		}
		state= (state + 1)%3;
		i += 2;
		break;
	}
	case 5: {
		if (getval(1) != 0) {
			i = getval(2);
		}
		else
		{
			i += 3;
		}
		break;
	}
	case 6: {
		if (getval(1) == 0) {
			i = getval(2);
		}
		else
		{
			i += 3;
		}
		break;
	}
	case 7: {
		getval(3) = getval(1) < getval(2);
		i += 4;
		break;
	}
	case 8: {
		getval(3) = getval(1) == getval(2);
		i += 4;
		break;
	}
	case 9: {
		base += getval(1);
		i += 2;
		break;
	}
	case 99:
		return 0;
	default:
		cout << "Oh no!";
	}
	return 1;
}

void part1() {
	while (cycle());
	int sum = 0;
	for (size_t y = 0; y < YLMT; y++)
	{
		for (size_t x = 0; x < XLMT; x++)
		{
			//cout << game[y][x];
			sum += game[y][x] == 2;
		}
		//cout << endl;
	}
	cout << sum << endl << endl;
	draw();
}

void part2() {
	s[0] = 2;
	while (cycle());
	cout << score;
}

int main() {
	char dump;
	for (i = 0; fin >> s[i]; i++) {
		fin.get(dump);
	}
	i = 0;

	part1();

	return 0;
}
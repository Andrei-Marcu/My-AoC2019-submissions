#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <utility>
#include <queue>

#define limit 10000
#define N 50

using namespace std;

typedef long long number;
typedef pair<number, number> packet;

bool part1 = true;

ifstream fin("input.txt");

number mem[limit], lastY = LLONG_MIN;

packet NAT;

struct Computer
{
	number* s, pc = 0, base = 0, readState = -1, writeState = 0, sendTo, id;

	bool isWorking = 1;

	queue<packet> buffer;

	packet toSend;

	Computer() {

	}

	Computer(number id, number* memory) {
		s = (number*)malloc(sizeof(number) * limit);
		memcpy(s, memory, sizeof(number) * limit);
		this->id = id;
	}

	//first parameter(excluding the opcode) is 1
	number& getval(int parameter) {
		switch (s[pc] / (number)pow(10ll, parameter + 1ll) % 10)
		{
		case 2:
			return s[base + s[pc + parameter]];
		case 1:
			return s[pc + parameter];
		case 0:
			return s[s[pc + parameter]];
		}
		cout << "Argh!";
		return s[0];
	}

	bool cycle() {
		switch (s[pc] % 100)
		{
		case 1: {
			getval(3) = getval(1) + getval(2);
			pc += 4;
			break;
		}
		case 2: {
			getval(3) = getval(1) * getval(2);
			pc += 4;
			break;
		}
		case 3: {
			switch (readState)
			{
			case 0:
				if (buffer.empty())
				{
					getval(1) = -1;
					isWorking = 0;
				}
				else
				{
					getval(1) = buffer.front().first;
					isWorking = 1;
					readState = 1;
				}
				break;
			case 1:
				getval(1) = buffer.front().second;
				buffer.pop();
				readState = 0;
				break;
			default:
				getval(1) = id;
				readState = 0;
			}
			pc += 2;
			break;
		}
		case 4: {
			switch (writeState)
			{
			case 0:
				sendTo = getval(1);
				writeState = 1;
				break;
			case 1:
				toSend.first = getval(1);
				writeState = 2;
				break;
			case 2:
				toSend.second = getval(1);
				if (sendTo >= N)
				{
					if (part1) {
						cout << toSend.second;
						return 0;
					}
					else
					{
						NAT = toSend;
						break;
					}
				}
				computers[sendTo].buffer.push(toSend);
				writeState = 0;
				break;
			}

			pc += 2;
			break;
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
			getval(3) = getval(1) < getval(2);
			pc += 4;
			break;
		}
		case 8: {
			getval(3) = getval(1) == getval(2);
			pc += 4;
			break;
		}
		case 9: {
			base += getval(1);
			pc += 2;
			break;
		}
		case 99:
			return 0;
		default:
			cout << "Oh no!";
		}
		return part1 || isWorking;
	}
}computers[N];

int main() {
	char dump;
	for (size_t i = 0; fin >> mem[i]; i++) {
		fin.get(dump);
	}
	//PART1
	for (size_t i = 0; i < N; i++)
	{
		computers[i] = Computer(i, mem);
	}
	while (true)
	{
		bool idle = 1;
		for (size_t i = 0; i < N; i++)
		{
			if (!computers[i].cycle()) {
				goto exit;
			}
		}
	}
exit:
	cout << ' ';
	//PART2
	for (size_t i = 0; i < N; i++)
	{
		computers[i] = Computer(i, mem);
	}
	part1 = false;

	while (true)
	{
		bool idle = 1;
		for (size_t i = 0; i < N; i++)
		{
			if (computers[i].cycle())
			{
				idle = 0;
			}
		}
		if (idle)
		{
			if (lastY == NAT.second)
			{
				cout << lastY;
				return 0;
			}
			lastY = NAT.second;
			computers[0].buffer.push(NAT);
			computers[0].isWorking = 1;
		}
	}
	return 0;
}
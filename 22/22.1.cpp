#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

typedef long long number;

#define COMMS 99
#define LIMIT 30

//
//
//
//
//	PART2 IS NOT WORKING!!!
//
//
//
//

//#define N 119315717514047LL
#define N 10007LL

//#define SHUFFLES 101741582076661
#define SHUFFLES 1

#define INC "deal with increment "
#define FLIP "deal into new stack"
#define CUT "cut "
//number pos = 2020LL;
number pos = 2019LL;

const short incLen = strlen(INC), cutLen = strlen(CUT);

char s[LIMIT + 1];

ifstream fin("input.txt");
ofstream fout("output.txt");

struct shuffle {
	number nr;
	shuffle(int nr): nr(nr){}
	virtual void perform() = 0;
	virtual void reverse() = 0;
};

struct cut : shuffle {
	cut(int nr): shuffle(nr < 0 ? N + nr : nr) {}
	void perform() {
		pos -= nr;
		if (pos < 0)
			pos += N;
	}
	void reverse() {
		pos += nr;
		if (pos >= N) {
			pos -= N;
		}
	}
};

struct flip : shuffle {
	flip() : shuffle(0) {}
	void perform() {
		pos = N - 1 - pos;
	}
	void reverse() {
		perform();
	}
};

struct incr : shuffle {
	//number* offsets;
	incr(int nr) : shuffle(nr) {
		//offsets = new number[nr];
		//for (size_t i = 0; i < nr; i++)
		//{
		//	//offset[i] = perform(i)
		//	//offsets[i] = i * nr % N;
		//	offsets[i] = sum;
		//	sum += ((N - i) / nr) + (bool)((N - i) % nr);
		//}
	}


	void perform() {
		pos *= nr;
		pos %= N;
	}
	void reverse() {
		while (pos % nr)
		{
			pos += N;
		}
		pos /= nr;
		/*auto offset = pos / nr;
		auto iter = pos % nr;*/
		//pos = offsets[pos % nr] + pos / nr;
	}
};

//vector<number> shifts;

int main() {
	shuffle *shuffles[COMMS + 1];
	int i = 0;
	for (;fin.getline(s, LIMIT);i++)
	{
		if (strstr(s, CUT))
		{
			shuffles[i] = new cut(atoi(s + cutLen));
		}
		else if (strstr(s, INC))
		{
			shuffles[i] = new incr(atoi(s + incLen));
		}
		else if (strstr(s, FLIP)) {
			shuffles[i] = new flip();
		}
		else
		{
			if (strlen(s) > 1)
				cout << "Hold up\n";
			continue;
		}
	}
	vector<number> nrs;
	for (auto shuffl : shuffles)
	{
		shuffl->perform();
		nrs.push_back(pos);
	}
	cout << pos;
	
	/*for (auto j = shuffles; j != shuffles + i; j++) {
		(*j)->reverse();
	}
	cout << pos;*/
	//shifts.push_back(pos);


	//for (number j = 0; j < SHUFFLES; j++)
	//{
	//	for (int i = COMMS; i != -1; i--) {
	//		shuffles[i]->reverse();
	//	}
	//	//if (pos == shifts.front())
	//	//{
	//	//	cout << shifts[SHUFFLES % shifts.size()]; // sure?
	//	//	/*auto mx = -1;
	//	//	for (auto& k : shifts)
	//	//	{
	//	//		if (mx < k) mx = k;
	//	//	}
	//	//	cout << mx;*/
	//	//	break;
	//	//}
	//	//else
	//	//{
	//	//	shifts.push_back(pos);
	//	//}
	//}
	//cout << pos;
}
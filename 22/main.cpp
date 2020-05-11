//#include <iostream>
//#include <fstream>
//#include <cstring>
//#include <cstdlib>
//
//using namespace std;
//
//#define LIMIT 30
//#define N 10007
//#define INC "deal with increment "
//#define FLIP "deal into new stack"
//#define CUT "cut "
//
//short x[N], y[N], * a = x, * b = y;
//const short incLen = strlen(INC), cutLen = strlen(CUT);
//
//char s[LIMIT + 1];
//
//ifstream fin("input.txt");
//ofstream fout("output.txt");
//
//void cut(int nr) {
//	if (nr < 0)
//		nr += N;
//	int i = 0;
//	for (; i < nr; i++) {
//		b[N - nr + i] = a[i];
//	}
//	for (; i < N; i++) {
//		b[i - nr] = a[i];
//	}
//}
//
//void flip() {
//	for (size_t i = 0; i < N; i++)
//	{
//		b[i] = a[N - i - 1];
//	}
//}
//
//void incr(int nr) {
//	size_t k = 0;
//	for (size_t i = 0; i < N; i++)
//	{
//		b[k] = a[i];
//		k += nr;
//		if (k >= N) {
//			k -= N;
//		}
//	}
//}
//
//int main() {
//	for (size_t i = 0; i < N; i++)
//	{
//		a[i] = i;
//	}
//	while (fin.getline(s, LIMIT))
//	{
//		if (strstr(s, CUT))
//		{
//			cut(atoi(s + cutLen));
//		}
//		else if (strstr(s,INC))
//		{
//			incr(atoi(s + incLen));
//		}
//		else if (strstr(s, FLIP)) {
//			flip();
//		}
//		else
//		{
//			if(strlen(s) > 1)
//				cout << "Hol' up\n";
//			continue;
//		}
//		swap(a, b);
//	}
//	size_t i = 0;
//	for (; a[i] != 2019; i++);
//	cout << i;
//}
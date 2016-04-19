#include "map.h"
#include <cstdio>
using namespace std;
Map<int, int> mp;
Set<int> st;
int main() {
	for (int i=0;i<10;++i) st[i]=100;
	st[0]+=1;
	for (int i=0;i<10;++i) printf("%d ", st[i]);
	return 0;
}
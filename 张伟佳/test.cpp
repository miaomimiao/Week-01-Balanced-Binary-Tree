#include "map.h"
#include <cstdio>
using namespace std;
Map<int, int> mp;
int main() {
	for (int i=0;i<10;++i) mp[i]=100;
	mp[0]+=1;
	for (int i=0;i<10;++i) printf("%d ", mp[i]);
	return 0;
}
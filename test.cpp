#include<iostream> 
#include<stdio.h>
#include<algorithm> 
#include<vector>
#include<deque>
#include<stack>
#include<queue>
#include<utility>

#define FOR(n) for(int i=0; i<n; i++) 
#define ROF(n) for(int i=n; i>0; i--) 
#define ri(c) scanf("%d",&c)
#define rii(c,cc) scanf("%d %d", &c, &cc)
#define riii(c,cc,ccc) scanf("%d %d %d", &c, &cc, &ccc)
	
using namespace std; 

int a[10];

void func(int a[])  {
	a[0] = 55; 
}

int main() 
{
	a[0] = 10;
	func(a);
	cout<<a[0]<<endl;
	return 0; 
}

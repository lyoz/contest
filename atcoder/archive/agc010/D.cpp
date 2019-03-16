#include <bits/stdc++.h>
using namespace std;

bool solve(vector<int>& a)
{
	int even=0,odd=0;
	for(auto x:a) (x&1?odd:even)++;
	assert(odd>=1);
	if(even&1) return true;
	if(odd>=2) return false;
	for(auto& x:a) if(x&1){
		if(x==1) return false;
		x--;
		break;
	}
	int g=a[0];
	for(auto x:a) g=__gcd(g,x);
	for(auto& x:a) x/=g;
	return !solve(a);
}

int main()
{
	for(int n;cin>>n&&n;){
		vector<int> a(n);
		rep(i,n) cin>>a[i];
		cout<<(solve(a)?"First":"Second")<<endl;
	}
}

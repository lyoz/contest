#include <bits/stdc++.h>
using namespace std;

using ll=long long;

ll fix(ll x,ll k)
{
	return (x+k-1)/k*k;
}

int main()
{
	for(int n;cin>>n&&n;){
		ll x=1,y=1;
		while(n--){
			ll a,b; cin>>a>>b;
			if(fix(x,a)/a*b>=y){
				x=fix(x,a);
				y=x/a*b;
			}
			else{
				y=fix(y,b);
				x=y/b*a;
			}
		}
		cout<<x+y<<endl;
	}
}

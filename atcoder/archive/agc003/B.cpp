#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int n;cin>>n && n;){
		vector<int> a(n);
		for(int& x:a) cin>>x;
		int64_t res=a[0]/2;
		a[0]%=2;
		for(int i=1;i<n;i++){
			int x=min(a[i-1],a[i]);
			res+=x;
			a[i]-=x;
			res+=a[i]/2;
			a[i]%=2;
		}
		cout<<res<<endl;
	}
}

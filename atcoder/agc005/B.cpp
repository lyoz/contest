#include <bits/stdc++.h>
using namespace std;

using ll=long long;

int main()
{
	for(int n;cin>>n && n;){
		vector<int> a(n),b(n);
		for(int i=0;i<n;i++)
			cin>>a[i],b[--a[i]]=i;
		map<int,int> range;
		range[0]=n;
		ll res=0;
		for(int x=0;x<n;x++){
			int i=b[x];
			auto it=--range.upper_bound(i);
			int l=it->first,r=it->second;
			res+=ll(x+1)*(i-l+1)*(r-i);
			range.erase(it);
			if(l<i) range[l]=i;
			if(i+1<r) range[i+1]=r;
		}
		cout<<res<<endl;
	}
}

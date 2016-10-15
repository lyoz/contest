#include <bits/stdc++.h>
using namespace std;

using ll=long long;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int n,q;cin>>n>>q && n|q;){
		vector<ll> qs(1,n);
		for(int i=0;i<q;i++){
			ll x; cin>>x;
			while(qs.size() && qs.back()>=x)
				qs.pop_back();
			qs.push_back(x);
		}
		vector<ll> cs(qs.size());
		cs.back()=1;
		vector<ll> res(n+1);
		for(int i=qs.size();i--;){
			for(;;){
				int j=upper_bound(begin(qs),begin(qs)+i,qs[i])-begin(qs)-1;
				if(j<0) break;
				cs[j]+=qs[i]/qs[j]*cs[i];
				qs[i]%=qs[j];
			}
			res[0]+=cs[i];
			res[qs[i]]-=cs[i];
		}
		for(int i=0;i<n;i++){
			cout<<res[i]<<endl;
			res[i+1]+=res[i];
		}
	}
}

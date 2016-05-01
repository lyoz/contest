#include <bits/stdc++.h>
using namespace std;

void solve_small(int k,int c,int s)
{
	if(s<k){
		cout<<"give up"<<endl;
		return;
	}
	assert(s==k);
	for(int i=0;i<s;i++){
		long long p=0;
		for(int j=0;j<c;j++)
			p=p*k+i;
		cout<<p+1<<(i<s-1?' ':'\n');
	}
}

void solve(int k,int c,int s)
{
	if(s*c<k){
		cout<<"IMPOSSIBLE"<<endl;
		return;
	}
	
	vector<long long> res;
	for(int i=0;i*c<k;i++){
		long long p=0;
		for(int j=0;j<c;j++){
			p=p*k+(i*c+j)%k;
		}
		res.push_back(p);
	}
	for(int i=0;i<res.size();i++)
		cout<<res[i]+1<<(i<res.size()-1?' ':'\n');
}

int main()
{
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		cout<<"Case #"<<_case<<": ";
		int k,c,s; cin>>k>>c>>s;
		//solve_small(k,c,s);
		solve(k,c,s);
	}
}

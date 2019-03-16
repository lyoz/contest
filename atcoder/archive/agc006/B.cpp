#include <bits/stdc++.h>
using namespace std;

void solve(int n,int x)
{
	if(x==1||x==2*n-1){
		cout<<"No"<<endl;
		return;
	}
	if(n==2){
		cout<<"Yes"<<endl;
		for(int x:{1,2,3})
			cout<<x<<endl;
		return;
	}
	vector<int> res;
	if(x==2){
		for(int i=3;i<=n;i++)
			res.push_back(i);
		res.push_back(2*n-1);
		res.push_back(x);
		res.push_back(1);
		res.push_back(2*n-2);
		for(int i=n+1;i<=2*n-3;i++)
			res.push_back(i);
	}
	else{
		for(int i=3;i<=n;i++) if(i!=x)
			res.push_back(i);
		res.push_back(1);
		res.push_back(x);
		res.push_back(2*n-1);
		res.push_back(2);
		for(int i=n+1;i<=2*n-2;i++) if(i!=x)
			res.push_back(i);
	}
	cout<<"Yes"<<endl;
	for(int x:res)
		cout<<x<<endl;
}

int main()
{
	for(int n,x;cin>>n>>x&&n|x;)
		solve(n,x);
}

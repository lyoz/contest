#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl

void solve()
{
	string s; cin>>s;
	string res;
	for(char c:s)
		res=max(res+c,c+res);
	cout<<res<<endl;
}

int main()
{
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		cout<<"Case #"<<_case<<": ";
		solve();
	}
}

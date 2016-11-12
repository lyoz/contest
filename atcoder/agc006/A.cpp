#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int n;cin>>n&&n;){
		string s,t; cin>>s>>t;
		for(int i=0;i<=n;i++)
			if(s.substr(0,i)+t.substr(0,n-i)==s){
				cout<<i+n<<endl;
				break;
			}
	}
}

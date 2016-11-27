#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(string s;cin>>s;){
		int res=0;
		for(int i=0;i<s.size();i++){
			int c="gp"[i&1];
			if(c!=s[i])
				res+=c=='p'?1:-1;
		}
		cout<<res<<endl;
	}
}

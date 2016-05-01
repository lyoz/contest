#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T; cin>>T;
	for(int _case=1;_case<=T;_case++){
		cout<<"Case #"<<_case<<": ";
		string s; cin>>s;
		int cnt=0;
		for(int i=0,j=0;i<s.size();i++){
			for(i=j;i<s.size() && s[i]=='+';i++);
			for(j=i;j<s.size() && s[j]=='-';j++);
			if(i<j) cnt++;
		}
		cout<<cnt*2-(s[0]=='-')<<endl;
	}
}

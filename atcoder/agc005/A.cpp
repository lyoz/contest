#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(string s;cin>>s;){
		string t;
		for(char c:s){
			if(t.size() && t.back()=='S' && c=='T')
				t.pop_back();
			else
				t+=c;
		}
		cout<<t.size()<<endl;
	}
}

#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(string s;cin>>s;){
		set<char> cs(begin(s),end(s));
		if(cs.size()==26){
			cout<<"None"<<endl;
			continue;
		}
		for(int i=0;i<26;i++)
			if(cs.count('a'+i)==0){
				cout<<char('a'+i)<<endl;
				break;
			}
	}
}

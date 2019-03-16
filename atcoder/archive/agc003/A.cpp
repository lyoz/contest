#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(string s;cin>>s;){
		int cnt[4]={};
		for(char c:s){
			if(c=='E') cnt[0]=1;
			if(c=='W') cnt[1]=1;
			if(c=='S') cnt[2]=1;
			if(c=='N') cnt[3]=1;
		}
		cout<<(cnt[0]==cnt[1]&&cnt[2]==cnt[3]?"Yes":"No")<<endl;
	}
}

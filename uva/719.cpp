#include <bits/stdc++.h>
using namespace std;

int lyndon(string s)
{
	int n=s.size(),i=0;
	s+=s;
	for(int j=1,k=0;j<n;j++){
		while(k<n && s[i+k]==s[j+k]) k++;
		if(s[i+k]<s[j+k])
			tie(j,k)=make_tuple(j+k,0);
		else if(s[i+k]>s[j+k])
			tie(i,j,k)=make_tuple(j,max(i+k,j),0);
	}
	return i;
}

int main()
{
	int T; cin>>T;
	while(T--){
		string s; cin>>s;
		cout<<s<<endl;
		cout<<lyndon(s)+1<<endl;
	}
}

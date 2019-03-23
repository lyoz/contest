#include <bits/stdc++.h>
using namespace std;

int main()
{
	for(int x,a,b;cin>>x>>a>>b&&x|a|b;){
		cout<<(abs(x-a)<abs(x-b)?"A":"B")<<endl;
	}
}

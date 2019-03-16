#include <bits/stdc++.h>
using namespace std;

constexpr int MOD=1000000007;

int main()
{
	for(int w;cin>>w&&w;){
		vector<string> grid(2);
		for(auto& s:grid) cin>>s;

		long long res=1;
		for(int j=0;j<w;){
			if(grid[0][j]==grid[1][j]){
				if(j==0)
					(res*=3)%=MOD;
				else if(grid[0][j-1]==grid[1][j-1])
					(res*=2)%=MOD;
				j++;
			}
			else{
				if(j==0)
					(res*=6)%=MOD;
				else if(grid[0][j-1]==grid[1][j-1])
					(res*=2)%=MOD;
				else
					(res*=3)%=MOD;
				j+=2;
			}
		}
		cout<<res<<endl;
	}
}

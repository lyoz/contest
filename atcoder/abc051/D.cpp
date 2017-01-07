#include <bits/stdc++.h>
using namespace std;

constexpr int INF=1e9;

int main()
{
	for(int n,m;cin>>n>>m&&n|m;){
		vector<tuple<int,int,int>> es;
		for(int i=0;i<m;i++){
			int u,v,w; cin>>u>>v>>w; u--,v--;
			es.emplace_back(u,v,w);
		}
		vector<vector<int>> dp(n,vector<int>(n,INF));
		for(int i=0;i<n;i++)
			dp[i][i]=0;
		for(auto e:es){
			int u,v,w; tie(u,v,w)=e;
			dp[u][v]=dp[v][u]=w;
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
		int res=0;
		for(auto e:es){
			int u,v,w; tie(u,v,w)=e;
			bool used=false;
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(dp[i][j]==dp[i][u]+w+dp[v][j]||dp[i][j]==dp[i][v]+w+dp[u][j])
						used=true;
			res+=!used;
		}
		cout<<res<<endl;
	}
}

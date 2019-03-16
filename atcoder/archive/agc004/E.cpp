#include <bits/stdc++.h>
using namespace std;

#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,n) repi(i,0,n)

using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;

inline int getsum(const vvi& sums,int t,int b,int l,int r)
{
	if(t>=b || l>=r) return 0;
	return sums[b][r]-sums[t][r]-sums[b][l]+sums[t][l];
}

inline int rsum(const vvi& sums,int i,int l,int r)
{
	return getsum(sums,i,i+1,l,r);
}

inline int csum(const vvi& sums,int t,int b,int j)
{
	return getsum(sums,t,b,j,j+1);
}

inline void chmax(int& a,int b)
{
	a=max(a,b);
}

int main()
{
	for(int h,w;cin>>h>>w && h|w;){
		vs grid(h);
		rep(i,h) cin>>grid[i];

		int ci=-1,cj=-1;
		rep(i,h) rep(j,w) if(grid[i][j]=='E') ci=i,cj=j;

		vvi sums(h+1,vi(w+1));
		rep(i,h) rep(j,w)
			sums[i+1][j+1]=(grid[i][j]=='o')+sums[i+1][j]+sums[i][j+1]-sums[i][j];

		int T=h-1-ci,B=ci,L=w-1-cj,R=cj;

		int dp[T+1][B+1][L+1][R+1]={};
		rep(t,T+1) rep(b,B+1) rep(l,L+1) rep(r,R+1){
			if(t!=T && ci+t+1<h-b)
				chmax(dp[t+1][b][l][r],dp[t][b][l][r]+rsum(sums,ci+(t+1),max(cj-r,l),min(cj+l+1,w-r)));
			if(b!=B && t<=ci-(b+1))
				chmax(dp[t][b+1][l][r],dp[t][b][l][r]+rsum(sums,ci-(b+1),max(cj-r,l),min(cj+l+1,w-r)));
			if(l!=L && cj+l+1<w-r)
				chmax(dp[t][b][l+1][r],dp[t][b][l][r]+csum(sums,max(ci-b,t),min(ci+t+1,h-b),cj+(l+1)));
			if(r!=R && l<=cj-(r+1))
				chmax(dp[t][b][l][r+1],dp[t][b][l][r]+csum(sums,max(ci-b,t),min(ci+t+1,h-b),cj-(r+1)));
		}

		int res=0;
		rep(t,T+1) rep(b,B+1) rep(l,L+1) rep(r,R+1) chmax(res,dp[t][b][l][r]);
		cout<<res<<endl;
	}
}

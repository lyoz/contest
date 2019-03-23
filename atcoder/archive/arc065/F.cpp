#include <bits/stdc++.h>
using namespace std;

#define dump(...) cout<<"# "<<#__VA_ARGS__<<'='<<(__VA_ARGS__)<<endl
#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define peri(i,a,b) for(int i=int(b);i-->int(a);)
#define rep(i,n) repi(i,0,n)
#define per(i,n) peri(i,0,n)
#define all(c) begin(c),end(c)
#define mp make_pair
#define mt make_tuple

using uint=unsigned;
using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using vd=vector<double>;
using vvd=vector<vd>;
using vs=vector<string>;

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}

template<typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
	print_tuple<Cdr...>(os,t);
	os<<(sizeof...(Cdr)?",":"")<<get<sizeof...(Cdr)>(t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
	print_tuple<Args...>(os<<'(',t);
	return os<<')';
}

template<typename Ch,typename Tr,typename C>
basic_ostream<Ch,Tr>& operator<<(basic_ostream<Ch,Tr>& os,const C& c){
	os<<'[';
	for(auto i=begin(c);i!=end(c);++i)
		os<<(i==begin(c)?"":" ")<<*i;
	return os<<']';
}

constexpr int INF=1e9;
constexpr int MOD=1e9+7;
constexpr double EPS=1e-9;

int main()
{
	for(int n,m;cin>>n>>m&&n|m;){
		string s; cin>>s;
		vi ls(m),rs(m);
		rep(i,m) cin>>ls[i]>>rs[i],ls[i]--;

		{
			vector<tuple<int,int>> ts;
			int pl=-1,pr=-1;
			rep(i,m) if(pr<rs[i]){
				if(pl<ls[i])
					ts.emplace_back(ls[i],rs[i]);
				else
					ts.back()=mt(ls[i],rs[i]);
				tie(pl,pr)=ts.back();
			}
			int first=get<0>(ts[0]),last=get<1>(ts.back());
			s=s.substr(first,last-first);
			n=s.size();
			m=ts.size();
			ls.resize(m),rs.resize(m);
			rep(i,m){
				tie(ls[i],rs[i])=ts[i];
				ls[i]-=first,rs[i]-=first;
			}
		}

		vi zcount(n+1),ocount(n+1);
		rep(i,n){
			zcount[i+1]=zcount[i];
			ocount[i+1]=ocount[i];
			(s[i]=='0'?zcount:ocount)[i+1]++;
		}

		vvi dp(n+1,vi(n+1));  // [文字数]['1'の使用回数]
		dp[0][0]=1;

		ls.push_back(n);
		rep(k,m){
			repi(i,ls[k],min(rs[k],ls[k+1]))
				rep(j,i+1){
					if(i+1-j<=zcount[rs[k]])
						(dp[i+1][j]+=dp[i][j])%=MOD;
					if(j+1<=ocount[rs[k]])
						(dp[i+1][j+1]+=dp[i][j])%=MOD;
				}
			repi(i,rs[k],ls[k+1])
				rep(j,i+1){
					if(s[i]=='0')
						(dp[i+1][j]+=dp[i][j])%=MOD;
					else
						(dp[i+1][j+1]+=dp[i][j])%=MOD;
				}
		}

		cout<<dp[n][ocount[n]]<<endl;
	}
}

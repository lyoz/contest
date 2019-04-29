#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cout<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cout<<endl;}while(0)
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

template<typename T,typename U>bool chmin(T& a,const U& b){return a>b?(a=b,1):0;}
template<typename T,typename U>bool chmax(T& a,const U& b){return a<b?(a=b,1):0;}

void print_vars(ostream&){}
template<typename Car,typename... Cdr>
void print_vars(ostream& os,const Car& car,const Cdr&... cdr){
	print_vars(os<<car<<(sizeof...(cdr)?",":""),cdr...);
}

template<typename T1,typename T2>
ostream& operator<<(ostream& os,const pair<T1,T2>& p){
	return os<<'('<<p.first<<','<<p.second<<')';
}

template<int I,typename Tuple>
void print_tuple(ostream&,const Tuple&){}
template<int I,typename Car,typename... Cdr,typename Tuple>
void print_tuple(ostream& os,const Tuple& t){
	os<<get<I>(t)<<(sizeof...(Cdr)?",":"");
	print_tuple<I+1,Cdr...>(os,t);
}
template<typename... Args>
ostream& operator<<(ostream& os,const tuple<Args...>& t){
	print_tuple<0,Args...>(os<<'(',t);
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

using vvvi=vector<vvi>;

template<typename T,typename Compare>
auto make_priority_queue(const Compare& comp)
{
	return priority_queue<T,vector<T>,Compare>(comp);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m;cin>>n>>m&&n|m;){
		string s; cin>>s;

		vvi f(26,vi(n+1,n));
		rep(i,n){
			vi& g=f[s[i]-'a'];
			for(int j=i;j>=0&&g[j]==n;j--)
				g[j]=i;
		}

		vvvi dp(251,vvi(251,vi(251,INF)));
		dp[0][0][0]=0;

		string x,y,z;
		rep(_,m){
			char t; int id; cin>>t>>id;
			if(t=='+'){
				char c; cin>>c;
				int i0=0,i1=x.size()+1;
				int j0=0,j1=y.size()+1;
				int k0=0,k1=z.size()+1;
				if(id==1) x+=c,i0=x.size()-1,i1=x.size()+1;
				if(id==2) y+=c,j0=y.size()-1,j1=y.size()+1;
				if(id==3) z+=c,k0=z.size()-1,k1=z.size()+1;
				repi(i,i0,i1) repi(j,j0,j1) repi(k,k0,k1) if(dp[i][j][k]!=INF){
					if(i!=x.size()){
						int v=f[x[i]-'a'][dp[i][j][k]];
						if(v!=n) chmin(dp[i+1][j][k],v+1);
					}
					if(j!=y.size()){
						int v=f[y[j]-'a'][dp[i][j][k]];
						if(v!=n) chmin(dp[i][j+1][k],v+1);
					}
					if(k!=z.size()){
						int v=f[z[k]-'a'][dp[i][j][k]];
						if(v!=n) chmin(dp[i][j][k+1],v+1);
					}
				}
			}
			else if(t=='-'){
				int i0=0,i1=251;
				int j0=0,j1=251;
				int k0=0,k1=251;
				if(id==1) i0=x.size(),i1=x.size()+1,x.pop_back();
				if(id==2) j0=y.size(),j1=y.size()+1,y.pop_back();
				if(id==3) k0=z.size(),k1=z.size()+1,z.pop_back();
				repi(i,i0,i1) repi(j,j0,j1) repi(k,k0,k1) if(dp[i][j][k]!=INF)
					dp[i][j][k]=INF;
			}
			cout<<(dp[x.size()][y.size()][z.size()]!=INF?"YES":"NO")<<endl;
		}
	}
}

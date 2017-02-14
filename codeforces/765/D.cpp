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
	for(int n;cin>>n&&n;){
		map<int,int> f;
		repi(x,1,n+1){
			int y; cin>>y;
			f[x]=y;
		}

		bool res=true;
		for(auto p:f){
			int x,y; tie(x,y)=p;
			if(y!=f[y]){
				res=false;
				break;
			}
		}
		if(!res){
			cout<<-1<<endl;
			continue;
		}

		map<int,int> g,hinv;
		for(auto p:f){
			int x,y; tie(x,y)=p;
			if(x==y)
				hinv.emplace(y,hinv.size()+1);
		}
		for(auto p:f){
			int x,y; tie(x,y)=p;
			g.emplace(x,hinv[f[y]]);
		}
		map<int,int> h;
		for(auto p:hinv){
			int x,y; tie(x,y)=p;
			h[y]=x;
		}

		vi gs,hs;
		for(auto p:g) gs.push_back(p.second);
		for(auto p:h) hs.push_back(p.second);
		int m=h.size();
		cout<<m<<endl;
		rep(i,gs.size()) cout<<gs[i]<<" \n"[i+1==g.size()];
		rep(i,hs.size()) cout<<hs[i]<<" \n"[i+1==h.size()];
	}
}

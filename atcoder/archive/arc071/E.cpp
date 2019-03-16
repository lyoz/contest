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
	for(string s,t;cin>>s>>t;){
		vi sa(s.size()+1),sb(s.size()+1),ta(t.size()+1),tb(t.size()+1);
		rep(i,s.size()){
			sa[i+1]=sa[i]+(s[i]=='A');
			sb[i+1]=sb[i]+(s[i]=='B');
		}
		rep(i,t.size()){
			ta[i+1]=ta[i]+(t[i]=='A');
			tb[i+1]=tb[i]+(t[i]=='B');
		}
		int q; cin>>q;
		rep(_,q){
			int a,b,c,d; cin>>a>>b>>c>>d; a--,c--;
			int x=((sa[b]-sa[a])-(sb[b]-sb[a])+999999)%3;
			int y=((ta[d]-ta[c])-(tb[d]-tb[c])+999999)%3;
			cout<<(x==y?"YES":"NO")<<endl;
		}
	}
}

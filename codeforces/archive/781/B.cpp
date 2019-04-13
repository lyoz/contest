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

string shorten(string name,string town)
{
	return name.substr(0,3);
}
string shorten2(string name,string town)
{
	return name.substr(0,2)+town[0];
}

void solve(vs names,vs towns)
{
	int n=names.size();
	vs res(n);
	map<string,int> f;
	rep(i,n){
		res[i]=shorten(names[i],towns[i]);
		f[res[i]]++;
	}
	vi conflicted(n);
	for(;;){
		bool updated=false;
		rep(i,n) if(!conflicted[i])
			if(f[res[i]]>=2){
				conflicted[i]=true;
				res[i]=shorten2(names[i],towns[i]);
				f[res[i]]++;
				updated=true;
			}
		if(!updated)
			break;
	}
	if(set<string>(all(res)).size()==n){
		cout<<"YES"<<endl;
		rep(i,n)
			cout<<res[i]<<endl;
	}
	else
		cout<<"NO"<<endl;
}

int main()
{
	for(int n;cin>>n&&n;){
		vs names(n),towns(n);
		rep(i,n) cin>>names[i]>>towns[i];
		solve(names,towns);
	}
}

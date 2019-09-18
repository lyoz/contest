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

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n;cin>>n&&n;){
		string s,t; cin>>s>>t;

		{
			map<char,int> f;
			for(char c:s) f[c]++;
			for(char c:t) f[c]++;
			bool ok=true;
			for(auto p:f) ok&=p.second%2==0;
			if(!ok){
				cout<<-1<<endl;
				continue;
			}
		}

		vi as,bs;
		rep(i,s.size()) if(s[i]!=t[i])
			(s[i]=='a'?as:bs).push_back(i);

		auto f=[](int x,int y){return to_string(x)+" "+to_string(y);};
		vs res;
		rep(i,as.size()/2){
			int j=as.size()-1-i;
			res.push_back(f(as[i]+1,as[j]+1));
		}
		rep(i,bs.size()/2){
			int j=bs.size()-1-i;
			res.push_back(f(bs[i]+1,bs[j]+1));
		}
		if(as.size()%2){
			int i=as.size()/2,j=bs.size()/2;
			res.push_back(f(as[i]+1,as[i]+1));
			res.push_back(f(as[i]+1,bs[j]+1));
		}
		cout<<res.size()<<endl;
		for(auto s:res)
			cout<<s<<endl;
	}
}

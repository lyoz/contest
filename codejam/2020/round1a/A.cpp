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

// Exactly one character of P_i is an asterisk (*), for all i.
// The leftmost character of P_i is the only asterisk (*), for all i.
void solve_set1(vs ss)
{
	int n=ss.size();
	rep(i,n)
		ss[i]=ss[i].substr(1);
	sort(all(ss),[](const string& a,const string& b){return a.size()>b.size();});

	string t=ss[0];
	rep(i,n){
		if(t.substr(t.size()-ss[i].size())!=ss[i]){
			cout<<'*'<<endl;
			return;
		}
	}
	cout<<t<<endl;
}

void solve()
{
	using vvs=vector<vs>;

	int n; cin>>n;
	vs ss(n);
	rep(i,n) cin>>ss[i];

	vs pres(n),sufs(n);
	vvs words(n);

	rep(i,n){
		string s=ss[i];
		replace(all(s),'*',' ');
		istringstream iss(s);
		if(ss[i][0]!='*')
			iss>>pres[i];
		for(string word;iss>>word;)
			words[i].push_back(word);
		if(ss[i].back()!='*'){
			sufs[i]=words[i].back();
			words[i].pop_back();
		}
	}

	string pre,suf;
	rep(i,n){
		if(pres[i]!=""){
			int len=min(pre.size(),pres[i].size());
			if(pre.substr(0,len)!=pres[i].substr(0,len)){
				cout<<'*'<<endl;
				return;
			}
			if(pre.size()<pres[i].size())
				pre=pres[i];
		}
		if(sufs[i]!=""){
			int len=min(suf.size(),sufs[i].size());
			if(suf.substr(suf.size()-len)!=sufs[i].substr(sufs[i].size()-len)){
				cout<<'*'<<endl;
				return;
			}
			if(suf.size()<sufs[i].size())
				suf=sufs[i];
		}
	}

	string res=pre;
	rep(i,n)
		for(string word:words[i])
			res+=word;
	res+=suf;

	cout<<res<<endl;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}

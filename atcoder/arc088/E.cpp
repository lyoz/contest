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

struct FenwickTree{
	vector<ll> data;
	FenwickTree(int n):data(n+1){}
	void Add(int i,int x){
		for(i++;i<data.size();i+=i&-i)
			data[i]+=x;
	}
	ll Sum(int i){
		ll res=0;
		for(;i;i-=i&-i)
			res+=data[i];
		return res;
	}
	ll Sum(int i,int j){
		return Sum(j)-Sum(i);
	}
};

ll calc(const vi& a)
{
	int n=a.size();
	FenwickTree ft(n);
	ll res=0;
	rep(i,n){
		res+=ft.Sum(a[i],n);
		ft.Add(a[i],1);
	}
	return res;
}

ll solve(const string& s)
{
	int n=s.size();
	map<char,deque<int>> pos;
	rep(i,n) pos[s[i]].push_back(i);

	int odd=0;
	for(auto p:pos) odd+=p.second.size()&1;
	if(odd>1) return -1;

	int pivot=-1;
	for(auto p:pos) if(p.second.size()&1){
		pivot=p.second[p.second.size()/2];
		break;
	}

	vi ls;
	for(auto p:pos){
		const auto a=p.second;
		int m=a.size()/2;
		ls.insert(end(ls),begin(a),begin(a)+m);
	}
	sort(all(ls));
	deque<int> rs;
	for(int i:ls){
		char c=s[i];
		rs.push_front(pos[c].back());
		pos[c].pop_back();
	}

	vi is=ls;
	if(n&1)
		is.push_back(pivot);
	is.insert(end(is),all(rs));
	return calc(is);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(string s;cin>>s&&s!="#";){
		cout<<solve(s)<<endl;
	}
}

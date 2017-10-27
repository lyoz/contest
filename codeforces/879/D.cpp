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

vector<tuple<ll,ll>> compress(const vector<tuple<ll,ll>>& b,ll n,ll k)
{
	vector<tuple<ll,ll>> res;
	ll cur=-1,cnt=0;
	rep(i,b.size()){
		ll x,c; tie(x,c)=b[i];
		if(x!=cur){
			if(cur!=-1)
				res.emplace_back(cur,cnt);
			cur=x,cnt=c;
		}
		else{
			(cnt+=c)%=k;
			if(cnt==0){
				if(res.empty())
					cur=-1;
				else{
					tie(cur,cnt)=res.back();
					res.pop_back();
				}
			}
		}
	}
	if(cnt>0)
		res.emplace_back(cur,cnt);
	if(res.size()>2*n){
		int l=n,r=res.size()-n;
		ll cnt=0;
		repi(i,l,r) cnt+=get<1>(res[i]);
		res.erase(begin(res)+l,begin(res)+r);
		res.emplace(begin(res)+l,INF,cnt);
	}
	return res;
}

ll solve(ll n,ll k,ll m,vl a)
{
	vector<vector<tuple<ll,ll>>> b(30);
	{
		vector<tuple<ll,ll>> t;
		rep(i,n) t.emplace_back(a[i],1);
		b[0]=compress(t,n,k);
	}
	repi(i,1,b.size()){
		vector<tuple<ll,ll>> t=b[i-1];
		t.insert(end(t),all(b[i-1]));
		b[i]=compress(t,n,k);
	}

	vector<tuple<ll,ll>> c;
	rep(i,30) if(m>>i&1){
		c.insert(end(c),all(b[i]));
		c=compress(c,n,k);
	}
	ll res=0;
	for(auto t:c) res+=get<1>(t);
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(ll n,k,m;cin>>n>>k>>m&&n|k|m;){
		vl a(n);
		rep(i,n) cin>>a[i];
		cout<<solve(n,k,m,a)<<endl;
	}
}

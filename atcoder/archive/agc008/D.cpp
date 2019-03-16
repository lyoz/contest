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

void solve(vi xs)
{
	int n=xs.size();

	vector<tuple<int,int>> ts(n);
	rep(i,n) ts[i]=mt(xs[i],i+1);
	sort(all(ts));

	deque<int> q;
	for(auto t:ts){
		int x=get<1>(t);
		rep(_,x-1) q.push_back(x);
	}

	vi occ(n+1),res;
	int p=0;
	for(auto t:ts){
		int i,x; tie(i,x)=t;
		for(;p<i;p++){
			if(q.empty()){
				cout<<"No"<<endl;
				return;
			}
			occ[q.front()]++;
			res.push_back(q.front());
			q.pop_front();
		}
		p=i+1;
		if(occ[x]<x-1){
			cout<<"No"<<endl;
			return;
		}
		res.push_back(x);
		rep(_,n-x) q.push_back(x);
	}

	while(q.size()){
		res.push_back(q.front());
		q.pop_front();
	}

	cout<<"Yes"<<endl;
	rep(i,res.size())
		cout<<res[i]<<" \n"[i+1==res.size()];
}

int main()
{
	for(int n;cin>>n&&n;){
		vi xs(n);
		rep(i,n) cin>>xs[i],xs[i]--;
		solve(xs);
	}
}

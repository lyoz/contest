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

const string UNSOLVABLE="UNSOLVABLE";

ll parse(const vi& a,const vi& p)
{
	ll res=0;
	rep(i,a.size())
		res=res*10+p[a[i]];
	return res;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(string a,b,c;cin>>a>>b>>c;){
		int n;
		vi x,y,z;
		{
			string cs=a+b+c;
			sort(all(cs));
			cs.erase(unique(all(cs)),end(cs));
			n=cs.size();
			if(n>10){
				cout<<UNSOLVABLE<<endl;
				continue;
			}
			rep(i,a.size())
				x.push_back(lower_bound(all(cs),a[i])-begin(cs));
			rep(i,b.size())
				y.push_back(lower_bound(all(cs),b[i])-begin(cs));
			rep(i,c.size())
				z.push_back(lower_bound(all(cs),c[i])-begin(cs));
		}

		ll res_a=-1,res_b=-1,res_c=-1;
		vi p(10); iota(all(p),0);
		do{
			if(p[x[0]]==0)
				continue;
			if(p[y[0]]==0)
				continue;
			if(p[z[0]]==0)
				continue;
			if(parse(x,p)+parse(y,p)==parse(z,p)){
				tie(res_a,res_b,res_c)=mt(parse(x,p),parse(y,p),parse(z,p));
				break;
			}
			reverse(n+all(p));
		}while(next_permutation(all(p)));

		if(res_a==-1)
			cout<<UNSOLVABLE<<endl;
		else
			cout<<res_a<<endl<<res_b<<endl<<res_c<<endl;
	}
}

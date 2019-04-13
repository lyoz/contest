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

int ModPow(int a,int r,int m)
{
	int x=1;
	for(;r;r>>=1){
		if(r&1) x=(ll)x*a%m;
		a=(ll)a*a%m;
	}
	return x;
}

tuple<vi,vvi> generate_input(int n,int m,int seed,int vmax)
{
	auto rnd=[&](){return exchange(seed,((ll)seed*7+13)%MOD);};
	vi a(n);
	rep(i,n) a[i]=rnd()%vmax+1;
	vvi qs;
	rep(i,m){
		int op=rnd()%4+1;
		int l=rnd()%n+1;
		int r=rnd()%n+1;
		if(l>r) swap(l,r);
		int x=op==3?rnd()%(r-l+1)+1:rnd()%vmax+1;
		if(op==4){
			int y=rnd()%vmax+1;
			qs.push_back({op,l,r,x,y});
		}
		else{
			qs.push_back({op,l,r,x});
		}
	}
	return mt(a,qs);
}

void split(map<int,tuple<int,ll>>& rs,int i)
{
	auto it=prev(rs.upper_bound(i));
	if(it->first==i) return;
	int r; ll x; tie(r,x)=it->second;
	it->second={i,x};
	rs[i]={r,x};
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int n,m,seed,vmax;cin>>n>>m>>seed>>vmax&&n|m|seed|vmax;){
		vi a;
		vvi qs;
		tie(a,qs)=generate_input(n,m,seed,vmax);

		rep(i,m) qs[i][1]--;  // l,rを0-originの半開区間にする
		map<int,tuple<int,ll>> rs;  // l->(r,x)
		rep(i,n) rs[i]={i+1,a[i]};

		for(auto q:qs){
			int op=q[0];
			int l=q[1],r=q[2],x=q[3];
			split(rs,l); split(rs,r);
			auto i=rs.lower_bound(l);
			auto j=rs.lower_bound(r);
			if(op==1){
				for(auto k=i;k!=j;k++)
					get<1>(k->second)+=x;
			}
			else if(op==2){
				for(auto k=i;k!=j;rs.erase(k++));
				rs[l]={r,x};
			}
			else if(op==3){
				x--;
				map<ll,int> f;
				for(auto k=i;k!=j;k++)
					f[get<1>(k->second)]+=get<0>(k->second)-k->first;
				int cnt=0;
				for(auto p:f)
					if(x<(cnt+=p.second)){
						cout<<p.first<<endl;
						break;
					}
			}
			else if(op==4){
				int y=q[4];
				map<ll,int> f;
				for(auto k=i;k!=j;k++)
					f[get<1>(k->second)]+=get<0>(k->second)-k->first;
				ll res=0;
				for(auto p:f)
					(res+=(ll)p.second*ModPow(p.first%y,x,y))%=y;
				cout<<res<<endl;
			}
		}
	}
}

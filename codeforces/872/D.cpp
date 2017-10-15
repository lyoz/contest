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

constexpr bool DEBUG=0;
vi debug_p,debug_b;

int query(int i,int j)
{
	printf("? %d %d\n",i,j); fflush(stdout);
	if(DEBUG){
		printf(">>> %d\n",debug_p[i]^debug_b[j]);
		return debug_p[i]^debug_b[j];
	}
	else{
		int x; scanf("%d",&x);
		return x;
	}
}

void answer(int m,const vi& p)
{
	printf("!\n%d\n",m);
	rep(i,p.size()) printf("%d%c",p[i],"\n "[i+1<p.size()]);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int n;
	if(DEBUG){
		scanf("%d",&n);
		debug_p.resize(n);
		debug_b.resize(n);
		rep(i,n) cin>>debug_p[i];
		rep(i,n) debug_b[debug_p[i]]=i;
		dump(debug_p); dump(debug_b);
	}
	else{
		scanf("%d",&n);
	}

	vi qs(n),cs(n);
	rep(i,n) qs[i]=query(i,0);
	rep(i,n) cs[i]=qs[0]^query(0,i);

	int cnt=0;
	vi res;
	rep(x,n){
		vi ps(n),bs(n);
		rep(i,n){
			ps[i]=qs[i]^x;
			bs[i]=cs[i]^x;
		}
		if(*max_element(all(ps))>=n||*max_element(all(bs))>=n)
			continue;
		bool ok=true;
		rep(i,n) ok&=bs[ps[i]]==i;
		if(ok){
			if(++cnt==1)
				res=ps;
		}
	}
	answer(cnt,res);
}

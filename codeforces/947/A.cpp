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

vi calc(const vi& xs,const vi& pfmax)
{
	vi fs(*max_element(all(xs))+2);
	for(int x:xs){
		set<int> ps;
		for(int t=x;t>1;){
			ps.insert(pfmax[t]);
			t/=pfmax[t];
		}
		for(int p:ps){
			int k=x/p;
			// p < y <= x
			// (k-1)p < y <= kp
			int l=max((k-1)*p,p),r=min(k*p,x);
			if(l>=r) continue;
			fs[l+1]++;
			fs[r+1]--;
		}
	}
	repi(i,1,fs.size()) fs[i]+=fs[i-1];
	vi ys;
	rep(i,fs.size()) if(fs[i]) ys.push_back(i);
	return ys;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	vi pfmax(1000050);
	repi(i,2,pfmax.size()) pfmax[i]=i;
	for(int i=2;i<pfmax.size();i++){
		if(pfmax[i]<i) continue;
		for(int j=i+i;j<pfmax.size();j+=i)
			pfmax[j]=i;
	}

	for(int x2;cin>>x2&&x2;){
		vi x1s=calc({x2},pfmax);
		vi x0s=calc(x1s,pfmax);
		cout<<x0s[0]<<endl;
	}
}

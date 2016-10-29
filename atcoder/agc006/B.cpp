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

int main()
{
	for(int n,x;cin>>n>>x && n|x;){
		int m=2*n-1;
		if(x==1 || x==m)
			cout<<"No"<<endl;
		else if(m==3){
			cout<<"Yes"<<endl;
			cout<<"1\n2\n3"<<endl;
		}
		else{
			vi res(m,-1);
			res[n-2]=1;
			res[n-1]=x;
			res[n]=m;
			deque<int> a;
			repi(i,1,m+1) if(1<i && i!=x && i<m) a.push_back(i);
			if(2<x){
				// ..., ?, 1, x, m, m-1, ...
				res[n+1]=2; a.pop_front();
				rep(i,n-2){res[i]=a[0]; a.pop_front();}
				repi(i,n+2,m){res[i]=a[0]; a.pop_front();}
			}
			else if(x<m-1){
				// ..., m-2, 1, x, m, ?, ...
				res[n-3]=m-1; a.pop_back();
				rep(i,n-3){res[i]=a[0]; a.pop_front();}
				repi(i,n+1,m){res[i]=a[0]; a.pop_front();}
			}
			cout<<"Yes"<<endl;
			rep(i,m) cout<<res[i]<<endl;
		}
	}
}

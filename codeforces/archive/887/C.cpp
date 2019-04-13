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

bool input(vi& faces)
{
	rep(i,24) cin>>faces[i];
	return !cin.eof();
}

void turn(vi& x,int a,int b,int c,int d)
{
	tie(x[a],x[b],x[c],x[d])=mt(x[d],x[a],x[b],x[c]);
}
void turn(vi& x,int a,int b,int c,int d,int e,int f,int g,int h)
{
	tie(x[a],x[b],x[c],x[d],x[e],x[f],x[g],x[h])=mt(x[g],x[h],x[a],x[b],x[c],x[d],x[e],x[f]);
}

void turn_u(vi& f,int n=1)
{
	rep(_,n){
		turn(f,0,1,3,2);
		turn(f,13,12,21,20,17,16,5,4);
	}
}

void turn_r(vi& f,int n=1)
{
	rep(_,n){
		turn(f,16,17,19,18);
		turn(f,3,1,20,22,11,9,7,5);
	}
}

void turn_f(vi& f,int n=1)
{
	rep(_,n){
		turn(f,4,5,7,6);
		turn(f,2,3,16,18,9,8,15,13);
	}
}

bool ok(const vi& f)
{
	rep(i,6){
		rep(j,4)
			if(f[i*4+j]!=f[i*4])
				return false;
	}
	return true;
}

void print(const vi& f)
{
	cout<<"  "<<f[0]<<f[1]<<endl;
	cout<<"  "<<f[2]<<f[3]<<endl;
	rep(i,2){
		for(int j:{12,13,4,5,16,17,20,21})
			cout<<f[i*2+j];
		cout<<endl;
	}
	cout<<"  "<<f[8]<<f[9]<<endl;
	cout<<"  "<<f[10]<<f[11]<<endl;
}

bool solve(vi& f)
{
	turn_u(f);
	if(ok(f)) return true;
	turn_u(f,2);
	if(ok(f)) return true;
	turn_u(f);

	turn_r(f);
	if(ok(f)) return true;
	turn_r(f,2);
	if(ok(f)) return true;
	turn_r(f);

	turn_f(f);
	if(ok(f)) return true;
	turn_f(f,2);
	if(ok(f)) return true;
	turn_f(f);

	return false;
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(vi faces(24);input(faces);){
		cout<<(solve(faces)?"YES":"NO")<<endl;
	}
}

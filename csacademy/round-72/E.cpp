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

struct Interval{
	int left,right;
	Interval(){}
	Interval(int l,int r):left(l),right(r){}
};
bool operator==(Interval a,Interval b){
	return a.left==b.left&&a.right==b.right;
}
ostream& operator<<(ostream& os,const Interval& i){
	return os<<mt(i.left,i.right);
}
struct LessLeft{
	bool operator()(Interval a,Interval b){
		return mt(a.left,a.right)<mt(b.left,b.right);
	}
};
struct LessRight{
	bool operator()(Interval a,Interval b){
		return mt(a.right,a.left)<mt(b.right,b.left);
	}
};

bool Intersect(Interval a,Interval b)
{
	return !(a.right<b.left||b.right<a.left);
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	for(int q;cin>>q&&q;){
		set<Interval,LessLeft> sl;
		set<Interval,LessRight> sr;
		rep(_,q){
			int t; cin>>t;
			if(t==1){
				int l,r; cin>>l>>r;
				sl.emplace(l,r);
				sr.emplace(l,r);
			}
			else if(t==2){
				int l,r; cin>>l>>r;
				sl.erase(Interval(l,r));
				sr.erase(Interval(l,r));
			}
			else if(t==3){
				Interval a,b; cin>>a.left>>a.right>>b.left>>b.right;
				if(a==b)
					cout<<0<<endl;
				else if(!Intersect(a,b))
					cout<<1<<endl;
				else{
					Interval c=*begin(sr),d=*--end(sl);
					if(!Intersect(a,c)&&!Intersect(c,b))
						cout<<2<<endl;
					else if(!Intersect(a,d)&&!Intersect(d,b))
						cout<<2<<endl;
					else if(!Intersect(a,c)&&!Intersect(c,d)&&!Intersect(d,b))
						cout<<3<<endl;
					else if(!Intersect(a,d)&&!Intersect(d,c)&&!Intersect(c,b))
						cout<<3<<endl;
					else
						cout<<-1<<endl;
				}
			}
		}
	}
}

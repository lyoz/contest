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

bool ok(int x,vi cs,vi ds)
{
	int n=cs.size();
	rep(i,n){
		if(ds[i]==1&&x<1900||ds[i]==2&&x>=1900)
			return false;
		x+=cs[i];
	}
	return true;
}

int calc(int x,vi cs)
{
	int n=cs.size();
	rep(i,n)
		x+=cs[i];
	return x;
}

string solve_naive(vi cs,vi ds)
{
	if(ok(INF,cs,ds))
		return "Infinity";
	for(int i=10000;i>=-10000;i--)
		if(ok(i,cs,ds))
			return to_string(calc(i,cs));
	return "Impossible";
}

string solve(vi cs,vi ds)
{
	int n=cs.size();
	//dump(n); dump(cs); dump(ds);

	if(count(all(ds),1)==n){
		return "Infinity";
	}
	if(count(all(ds),2)==n){
		int x=0,mx=0;
		rep(i,n-1){
			x+=cs[i];
			mx=max(mx,x);
		}
		int offset=1899-mx;
		return to_string(offset+x+cs.back());
	}

	rep(i,n-1){
		if(ds[i]==1&&ds[i+1]==2){
			if(cs[i]>=0)
				return "Impossible";
			int mn=1900,mx=1899-cs[i];
			rep(j,i){
				mn-=cs[j];
				mx-=cs[j];
			}
			//dump(mt(i,"1->2",cs[i],mn,mx));
			for(int x=mx;x>=mn;x--)
				if(ok(x,cs,ds))
					return to_string(calc(x,cs));
			return "Impossible";
		}
		else if(ds[i]==2&&ds[i+1]==1){
			if(cs[i]<=0)
				return "Impossible";
			int mn=1900-cs[i],mx=1899;
			rep(j,i){
				mn-=cs[j];
				mx-=cs[j];
			}
			//dump(mt(i,"2->1",cs[i],mn,mx));
			for(int x=mx;x>=mn;x--)
				if(ok(x,cs,ds))
					return to_string(calc(x,cs));
			return "Impossible";
		}
	}

	assert(0);
}

// [a,b)
int randrange(int a,int b)
{
	return a+rand()/(RAND_MAX+1.)*(b-a);
}
int randint(int a,int b)
{
	return randrange(a,b+1);
}

int main()
{
	//for(;;){
	//	int n=5;
	//	vi cs(n),ds(n);
	//	rep(i,n){
	//		cs[i]=randint(-10,10);
	//		ds[i]=randint(1,2);
	//	}
	//	string res=solve(cs,ds);
	//	string ans=solve_naive(cs,ds);
	//	if(res!=ans){
	//		cout<<n<<endl;
	//		rep(i,n) cout<<cs[i]<<' '<<ds[i]<<endl;
	//		dump(res); dump(ans);
	//		return 1;
	//	}
	//}

	for(int n;cin>>n&&n;){
		vi cs(n),ds(n);
		rep(i,n) cin>>cs[i]>>ds[i];
		cout<<solve(cs,ds)<<endl;
	}
}

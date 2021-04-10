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

void solve_set1(int n,int q,vs as,vi ss)
{
	vi bs(n);
	rep(i,n){
		rep(j,q)
			bs[i]|=(as[i][j]=='T')<<j;
	}
	//dump(bs);
	vi ts; // 模範解答として考えられるもの
	rep(s,1<<q){
		bool ok=true;
		rep(i,n){
			int cnt=0;
			rep(j,q)
				cnt+=(s>>j&1)==(bs[i]>>j&1);
			if(cnt!=ss[i]){
				ok=false;
				break;
			}
		}
		//dump(s,ok);
		if(ok)
			ts.push_back(s);
	}
	//dump(ts);

	int res=0;
	int num=0,den=ts.size();
	rep(i,q){
		int cnt=0;
		rep(j,ts.size()){
			cnt+=ts[j]>>i&1;
		}
		if(cnt*2>=ts.size()){
			res|=1<<i;
			num+=cnt;
		}
		else{
			num+=ts.size()-cnt;
		}
	}
	//dump(res,num,den);

	int g=gcd(num,den);
	num/=g,den/=g;
	rep(i,q)
		cout<<"FT"[res>>i&1];
	cout<<" "<<num<<"/"<<den<<endl;
}

void solve_set2(int n,int q,vs as,vi ss)
{
	if(n==1){
		if(ss[0]*2>=q)
			cout<<as[0]<<" "<<ss[0]<<"/1"<<endl;
		else{
			rep(i,q)
				cout<<(as[0][i]=='T'?'F':'T');
			cout<<" "<<q-ss[0]<<"/1"<<endl;
		}
		return;
	}

	if(ss[0]<ss[1]){
		swap(as[0],as[1]);
		swap(ss[0],ss[1]);
	}
	//dump(n,q,as,ss);
	int same=0,diff=0;
	rep(i,q){
		if(as[0][i]==as[1][i])
			same++;
		else
			diff++;
	}
	int diff_ac=(ss[0]-ss[1]+diff)/2;
	int same_ac=ss[0]-diff_ac;
	//dump(diff_ac,same_ac);

	int num=max(same_ac,same-same_ac)+max(diff_ac,diff-diff_ac);
	rep(i,q){
		if(as[0][i]==as[1][i]){
			if(same_ac*2>=same)
				cout<<as[0][i];
			else
				cout<<(as[0][i]=='T'?'F':'T');
		}
		else{
			if(diff_ac*2>=diff)
				cout<<as[0][i];
			else
				cout<<(as[0][i]=='T'?'F':'T');
		}
	}
	cout<<" "<<num<<"/1"<<endl;
}

void solve()
{
	int n,q; cin>>n>>q;
	vs as(n);
	vi ss(n);
	rep(i,n) cin>>as[i]>>ss[i];
	//dump(n,q,as,ss);

	if(n<=2&&q<=10){ // set1
		solve_set2(n,q,as,ss);
	}
	else if(n<=2&&q<=40){ // set2
		solve_set2(n,q,as,ss);
	}
	else{
		cout<<"X"<<endl;
	}
}

int main()
{
	#ifndef _GLIBCXX_DEBUG
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	constexpr char endl='\n';
	#endif

	int tc; cin>>tc;
	rep(i,tc){
		cout<<"Case #"<<i+1<<": ";
		solve();
	}
}

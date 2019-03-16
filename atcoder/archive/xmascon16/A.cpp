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

void solve1()
{
	int n; scanf("%d",&n);
	int res=0;
	for(int i=0;i<20;i++){
		if(n>>i&1){
			printf("? %d %d\n",n-(1<<i),n);
			fflush(stdout);
			int x; scanf("%d",&x);
			res+=x;
			n-=1<<i;
		}
	}
	printf("! %d\n",res);
}

int input()
{
	int x;
	return scanf("%d",&x),x;
}

int query(int a,int b)
{
	printf("? %d %d\n",a,b);
	fflush(stdout);
	return input();
}

void answer(int x)
{
	printf("! %d\n",x);
	fflush(stdout);
}

void solve2()
{
	int n=input();

	vi twos;
	for(int i=1;i<=n;i*=2)
		twos.push_back(i);

	vvi memo(n+1);
	queue<int> q;
	for(int x:twos){
		memo[x].push_back(x);
		q.push(x);
	}

	while(q.size()){
		int cur=q.front(); q.pop();
		for(int x:twos){
			if(cur-x>0 && memo[cur-x].empty()){
				(memo[cur-x]=memo[cur]).push_back(-x);
				q.push(cur-x);
			}
			if(cur+x<=n && memo[cur+x].empty()){
				(memo[cur+x]=memo[cur]).push_back(x);
				q.push(cur+x);
			}
		}
	}

	int sum=0,cur=0;
	for(int x:memo[n]){
		if(x>0)
			sum+=query(cur,cur+x);
		else
			sum-=query(cur+x,cur);
		cur+=x;
	}
	answer(sum);
}

int main()
{
	//solve1();
	solve2();
}

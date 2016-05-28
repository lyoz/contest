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

template<typename T>
struct functor_traits:public functor_traits<decltype(&T::operator())>{};
template<typename C,typename Ret,typename... Args>
struct functor_traits<Ret(C::*)(Args...)const>{
	template<size_t I>
	using nth_argument_type=typename tuple_element<I,tuple<Args...>>::type;
	using first_argument_type=nth_argument_type<0>;
};
template<typename Compare,typename T=typename decay<typename functor_traits<Compare>::first_argument_type>::type>
priority_queue<T,vector<T>,Compare> make_priority_queue(Compare comp){
	return priority_queue<T,vector<T>,Compare>(comp);
}

int main()
{
	for(int n;cin>>n&&n;){
		vi ts(n);
		rep(i,n) cin>>ts[i],ts[i]--;
		
		vi res(n);
		rep(i,n){
			vi cs(n);
			auto pq=make_priority_queue([](tuple<int,int> a,tuple<int,int> b){
				int ac,ai,bc,bi; tie(ac,ai)=a; tie(bc,bi)=b;
				return ac!=bc?ac<bc:ai>bi;
			});
			repi(j,i,n){
				pq.emplace(++cs[ts[j]],ts[j]);
				res[get<1>(pq.top())]++;
			}
		}
		rep(i,n) cout<<res[i]<<(i<n-1?' ':'\n');
	}
}

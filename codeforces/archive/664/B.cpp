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

vs split(const string& s)
{
	vs res;
	istringstream iss(s);
	for(string t;iss>>t;)
		res.push_back(t);
	return res;
}

int main()
{
	for(string line;getline(cin,line) && line!="#";){
		vs tokens=split(line);
		int n=stoi(tokens.back());
		vi is_plus;
		rep(i,tokens.size()/2)
			is_plus.push_back(i==0 || tokens[i*2-1]=="+");
		
		int mn=0,mx=0;
		rep(i,is_plus.size())
			if(is_plus[i])
				mn++,mx+=n;
			else
				mn-=n,mx--;
		
		if(mn<=n && n<=mx){
			cout<<"Possible"<<endl;
			int res=0;
			vi xs(is_plus.size(),1);
			rep(i,is_plus.size())
				if(is_plus[i])
					res++;
				else
					res--;
			for(int i=0;res<n;i++) if(is_plus[i]){
					int add=min(n-res,n-1);
					xs[i]+=add;
					res+=add;
			}
			for(int i=0;res>n;i++) if(!is_plus[i]){
					int sub=min(res-n,n-1);
					xs[i]+=sub;
					res-=sub;
			}
			cout<<xs[0];
			repi(i,1,xs.size())
				cout<<(is_plus[i]?" + ":" - ")<<xs[i];
			cout<<" = "<<n<<endl;
		}
		else
			cout<<"Impossible"<<endl;
	}
}

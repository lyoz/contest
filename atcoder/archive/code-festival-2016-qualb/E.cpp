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

constexpr int ALPHABET=26;

int ToInt(char c)
{
	return c-'a';
}

char ToChar(int x)
{
	return x+'a';
}

struct Node{
	char value;
	shared_ptr<Node> parent;
	array<shared_ptr<Node>,ALPHABET> children;
	bool last;
	int count;
	Node(char v):value(v),last(false),count(0){}
};

struct Patricia{
	shared_ptr<Node> root;
	vector<shared_ptr<Node>> lasts;
	Patricia():root(make_shared<Node>('!')){}
	void Add(const string& s){
		auto cur=root;
		for(char c:s){
			auto& child=cur->children[ToInt(c)];
			if(!child){
				child=make_shared<Node>(c);
				child->parent=cur;
			}
			cur=child;
			cur->count++;
		}
		cur->last=true;
		lasts.push_back(cur);
	}
	void Compress(){
		for(auto cur:lasts){
			while(cur && cur->parent && cur->parent->parent){
				auto p=cur->parent,g=p->parent;
				if(cur->count==p->count){
					g->children[ToInt(p->value)]=cur;
					cur->value=p->value;
					cur->parent=g;
				}
				else
					cur=p;
			}
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for(int n;cin>>n && n;){
		vs ss(n);
		rep(i,n) cin>>ss[i];
		int q; cin>>q;
		vi ks(q);
		vs ps(q);
		rep(i,q){
			cin>>ks[i]>>ps[i];
			ks[i]--;
		}

		Patricia pt;
		vector<shared_ptr<Node>> lasts;
		for(auto s:ss) pt.Add(s);

		pt.Compress();

		rep(_,q){
			string p=ps[_];
			int res=0;
			for(auto cur=pt.lasts[ks[_]];cur!=pt.root;cur=cur->parent){
				if(cur->last) res++;
				for(char c:p){
					if(c==cur->value) break;
					if(cur->parent->children[ToInt(c)])
						res+=cur->parent->children[ToInt(c)]->count;
				}
			}
			cout<<res<<endl;
		}
	}
}

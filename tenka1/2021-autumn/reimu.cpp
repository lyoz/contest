#include <bits/stdc++.h>
using namespace std;

#define dump(...) do{print_vars(cerr<<"# "<<#__VA_ARGS__<<'=',__VA_ARGS__);cerr<<endl;}while(0)
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

struct AgentMove{
	double x,y;
	int t;
};

struct Agent{
	vector<AgentMove> moves;
};

struct Resource{
	int id,x,y,t0,t1;
	string type;
	int weight;
};

struct ResourceWithAmount:Resource{
	double amount;
};

struct OwnedResource{
	string type;
	double amount;
};

struct Game{
	int now;
	vector<Agent> agents;
	vector<Resource> resources;
	int next_resource;
	vector<OwnedResource> owned_resources;
};

struct Move{
	int now;
	vector<AgentMove> moves;
};

Game call_game()
{
	cout<<"game"<<endl;
	Game res;
	int acnt,rcnt,orcnt;
	cin>>res.now>>acnt>>rcnt>>res.next_resource>>orcnt;

	res.agents.resize(acnt);
	for(auto& a:res.agents){
		int mcnt; cin>>mcnt;
		a.moves.resize(mcnt);
		for(auto& m:a.moves)
			cin>>m.x>>m.y>>m.t;
	}

	res.resources.resize(rcnt);
	for(auto& r:res.resources)
		cin>>r.id>>r.x>>r.y>>r.t0>>r.t1>>r.type>>r.weight;

	res.owned_resources.resize(orcnt);
	for(auto& r:res.owned_resources)
		cin>>r.type>>r.amount;

	return res;
}

vector<ResourceWithAmount> call_resources(vi is){
	cout<<"resources";
	for(auto i:is)
		cout<<' '<<i;
	cout<<endl;
	int rcnt; cin>>rcnt;
	vector<ResourceWithAmount> res(rcnt);
	for(auto r:res)
		cin>>r.id>>r.x>>r.y>>r.t0>>r.t1>>r.type>>r.weight>>r.amount;
	return res;
}

Move read_move()
{
	Move res;
	int mcnt;
	cin>>res.now>>mcnt;
	res.moves.resize(mcnt);
	for(auto& m:res.moves)
		cin>>m.x>>m.y>>m.t;
	return res;
}

Move call_will_move(int i,int x,int y,int t)
{
	cout<<"will_move "<<i<<' '<<x<<' '<<y<<' '<<t<<endl;
	return read_move();
}

void print_game(const Game& g)
{
	cerr<<"# ======== game ========"<<endl;
	dump(g.now);
	cerr<<"# agents:"<<endl;
	for(auto a:g.agents){
		for(auto m:a.moves)
			cerr<<'('<<m.x<<','<<m.y<<','<<m.t<<')';
		cerr<<endl;
	}
	cerr<<"# resources:"<<endl;
	for(auto r:g.resources)
		cerr<<'('<<r.id<<','<<r.x<<','<<r.y<<','<<r.t0<<','<<r.t1<<','<<r.type<<','<<r.weight<<')'<<endl;
	dump(g.next_resource);
	cerr<<"# owned resources:"<<endl;
	for(auto r:g.owned_resources)
		cerr<<'('<<r.type<<','<<r.amount<<')';
	cerr<<endl;
}

void sleep(int ms)
{
	this_thread::sleep_for(chrono::milliseconds(ms));
}

constexpr int AGENT_NUM=5;
constexpr double AGENT_SPEED=0.1; // 1ミリ秒あたり0.1動ける

int main()
{
	for(;;){
		Game game=call_game();
		print_game(game);

		map<string,double> type_weights;
		{
			auto rs=game.owned_resources;
			sort(all(rs),[](auto a,auto b){return a.amount<b.amount;});
			type_weights[rs[0].type]=1;
			type_weights[rs[1].type]=0.1;
			type_weights[rs[2].type]=0.01;
			for(auto& r:rs) dump(r.type,r.amount);
		}
		rep(ai,game.agents.size()){
			Agent a=game.agents[ai];
			if(a.moves.back().t>game.now) // 移動中
				continue;
			AgentMove cur=a.moves.back();
			double cand=0;
			int nx=0,ny=0,ni=-1;
			for(auto r:game.resources){
				int dx=r.x-cur.x,dy=r.y-cur.y;
				double d=sqrt(dx*dx+dy*dy);
				double t0=max<double>(game.now+d/AGENT_SPEED,r.t0); // 回収開始時刻
				double t1=min<double>(r.t1,game.now+2000); // 回収終了時刻(2秒後まで考える)
				double t=max<double>(t1-t0,0);
				double amount=r.weight*type_weights[r.type]*t/1000;
				if(cand<amount){
					cand=amount;
					nx=r.x,ny=r.y,ni=r.id;
				}
			}
			if(ni==-1)
				continue;
			cerr<<"# agent "<<ai+1<<": ("<<cur.x<<','<<cur.y<<")->("<<nx<<','<<ny<<')'<<endl;
			call_will_move(ai+1,nx,ny,game.now);
			rep(ri,game.resources.size())
				if(game.resources[ri].id==ni){
					game.resources.erase(begin(game.resources)+ri);
					break;
				}
			//sleep(150);
		}
		//sleep(1500);
	}
}

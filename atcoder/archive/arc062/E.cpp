#include <bits/stdc++.h>
using namespace std;

#define repi(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,n) repi(i,0,n)
#define all(c) begin(c),end(c)

using ll=long long;
using Tile=array<int,4>;
using Faces=array<Tile,4>;

Tile normalize(Tile a)
{
	Tile res=a;
	rep(i,3){
		rotate(all(a)-1,end(a));
		res=min(res,a);
	}
	return res;
}

ll npr(int n,int p)
{
	ll res=1;
	rep(i,p) res*=n-i;
	return res;
}

ll calc(const vector<Tile>& tiles,map<Tile,ll>& freq,int ti,int bi)
{
	Faces faces={
		normalize(Tile{tiles[ti][1],tiles[ti][0],tiles[bi][1],tiles[bi][0]}),
		normalize(Tile{tiles[ti][2],tiles[ti][1],tiles[bi][0],tiles[bi][3]}),
		normalize(Tile{tiles[ti][3],tiles[ti][2],tiles[bi][3],tiles[bi][2]}),
		normalize(Tile{tiles[ti][0],tiles[ti][3],tiles[bi][2],tiles[bi][1]}),
	};
	map<Tile,int> face_count;
	for(auto f:faces) face_count[f]++;
	ll res=1;
	for(auto p:face_count){
		Tile face=p.first;
		int n=freq[face]-(face==tiles[ti])-(face==normalize(tiles[bi]));
		res*=npr(n,p.second);
	}
	for(Tile f:faces)
		if(f[0]==f[2]&&f[1]==f[3]){
			res*=2;
			if(f[0]==f[1])
				res*=2;
		}
	return res;
}

int main()
{
	for(int n;cin>>n&&n;){
		vector<Tile> tiles;
		rep(i,n){
			int a,b,c,d; cin>>a>>b>>c>>d;
			tiles.emplace_back(normalize({a,b,c,d}));
		}

		map<Tile,ll> freq;
		rep(i,n) freq[tiles[i]]++;

		ll res=0;
		rep(i,n) repi(j,i+1,n) rep(k,4){
			res+=calc(tiles,freq,i,j);
			rotate(all(tiles[j])-1,end(tiles[j]));
		}
		cout<<res/3<<endl;
	}
}

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
#define MAX 1000000
typedef pair<unsigned int, int> WeightNode;
int Adj[500][500];

int dijkstra(int S, int D, int N) {
	unsigned int Dist[N];
	int previous[N];
	priority_queue<WeightNode, vector<WeightNode>, greater<WeightNode> > Q;
	for(int i=1; i<N; ++i) {
		Dist[i]=MAX;
		previous[i] = N+1;
	}
	Dist[0] = 0;
	Q.push(make_pair(0,S));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		for(int v=0; v<N; ++v) {
			if(Adj[u][v]<MAX && v!=u) {
				if(Dist[v]>Dist[u]+Adj[u][v]) {
					Dist[v] = Dist[u] + Adj[u][v];
					previous[v] = u;
					Q.push(make_pair(Dist[v],v));
				}
			}
		}	
	}
	if(Dist[D]==MAX) return -1;
	//To set the shortest path to MAX
	int i=D;
	while(i != S) {
		Adj[previous[i]][i] = MAX;
		i = previous[i];
	}
	return Dist[D];
}

int main() {
	int N,M,S,D;
	while(true) {
		scanf("%d %d", &N, &M);
		if(N==0 && M==0) break;
		scanf("%d %d", &S, &D);
		int x,y,d,nearest,almostNearest;
		//To store the graph into Matrix Adj
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
				Adj[i][j]=MAX;
		for(int i=0; i<M; ++i) {
			scanf("%d %d %d", &x,&y,&d);
			Adj[x][y] = d;
		}

		nearest = dijkstra(S,D,N);
		almostNearest = dijkstra(S,D,N);
		//IF nearest = checkNearest : it is not the ALMOST path, do this again!
		while(almostNearest==nearest) {
			almostNearest = dijkstra(S,D,N);
		}

		cout << almostNearest << endl;
	}
	return 0;
}
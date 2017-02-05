#include <bits/stdc++.h>
using namespace std;

const int INF = 1.0e9;
const int NEG_INF = -1.0e9;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int debugging = 1;

const int MAX_V = 10;
int s, t, mF, pF; // s = src, t = sink, mF = maxFlow, pF = minPathFlow
vector<vii> G; // Graph using Adj List
int rG[MAX_V][MAX_V]; // Residual Graph using Adj Matrix, stores weight of edge (row -> col)
vi p; // Path found by BFS

void augment(int v, int minEdge) {     // traverse BFS spanning tree from s to t
  if (v == s) { pF = minEdge; return; }  // record minEdge in a global variable f
  else if (p[v] != -1) { augment(p[v], min(minEdge, rG[p[v]][v])); // recursive
                         rG[p[v]][v] -= pF; rG[v][p[v]] += pF; }       // update
}

// O(VE^2) Edmonds-Karp's algorithm
void edmondsKarp() {
    mF = 0;
    while (1) {
        pF = 0;
        bitset<MAX_V> vis; vis[s] = true; // we change vi dist to bitset!
        queue<int> q; q.push(s); // BFS portion of the code
        p.assign(MAX_V, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            forn (j, (int)G[u].size()) {
                int v = G[u][j].first;
                if (rG[u][v] > 0 && !vis[v])
                    vis[v] = true, q.push(v), p[v] = u;
        }}
        augment(t, INF); // find the min edge weight `f' along this path, if any
        if (pF == 0) break; // we cannot send any more flow (`f' = 0), terminate
        mF += pF;   // we can still send a flow, increase the max flow!
    }
}

int main() {
	FASTER;
	// Initialize and populate G and rG
	int V = 7; s = 0; t = 6;
    memset(rG, 0, sizeof rG);
    G.assign(V, vii());
    G[0].push_back(ii(1, 25)); rG[0][1] = 25;
    G[0].push_back(ii(2, 9)); rG[0][2] = 9;
    G[1].push_back(ii(0, 25)); rG[1][0] = 25;
    G[1].push_back(ii(3, 13)); rG[1][3] = 13;

    G[2].push_back(ii(0, 9));  rG[2][0] = 9;
    G[2].push_back(ii(3, 17)); rG[2][3] = 17;

    G[3].push_back(ii(2, 9));  rG[3][2] = 9;
    G[3].push_back(ii(5, 20)); rG[3][5] = 20;
    G[4].push_back(ii(3, 7));  rG[4][3] = 7;
    G[4].push_back(ii(5, 4));  rG[4][5] = 4;

    edmondsKarp(); printf("Maxflow from %d to %d: %d\n", s, t, mF); // 18

	return 0;
}

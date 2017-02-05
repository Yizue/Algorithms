#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#define DFS_WHITE -1

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int debugging = 1;

int V = 8;
vector<vii> G;
vector<vi> SCC; // List of the SCC's
vi dfs_low, dfs_num, vis, S; // DFS values used in Tarjan's Algorithm
int dfsNumCounter, numSCC;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumCounter++;      // dfs_low[u] <= dfs_num[u]
    S.push_back(u);           // stores u in a vector based on order of visitation
    vis[u] = 1;
    for (int j = 0; j < (int)G[u].size(); j++) {
        ii v = G[u][j];
        if (dfs_num[v.first] == DFS_WHITE)
            tarjanSCC(v.first);
        if (vis[v.first])                                // condition for update
            dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
    }
    if (dfs_low[u] == dfs_num[u]) {    // if this is a root (start) of an SCC
        while (1) { // grab all the members for this SCC
            int v = S.back(); S.pop_back(); vis[v] = 0;
            SCC[numSCC].push_back(v);
            if (u == v) { numSCC++; break; }
        }
} }


int main()
{
    FASTER;
    G.assign(V, vii());
    G[0].push_back(ii(1, 1));
	G[1].push_back(ii(2, 1));
	G[2].push_back(ii(0, 1));
	G[2].push_back(ii(1, 1));
	G[2].push_back(ii(3, 1));
	G[3].push_back(ii(4, 1));
	G[4].push_back(ii(5, 1));
	G[5].push_back(ii(6, 1));
	G[5].push_back(ii(7, 1));
	G[6].push_back(ii(4, 1));
	//G[7].push_back(ii(5, 1));

    printf("Strongly Connected Components (the input graph must be DIRECTED)\n");
    dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0); vis.assign(V, 0);
    SCC.assign(V, vi());
    dfsNumCounter = numSCC = 0;
    forn (i, V)
        if (dfs_num[i] == DFS_WHITE)
            tarjanSCC(i);
    forn (j, numSCC) {
        printf("SCC %d: ", j);
        forn (k, (int)SCC[j].size()) {
            printf("%d ", SCC[j][k]);
        }
        printf("\n");
    }

    return 0;
}


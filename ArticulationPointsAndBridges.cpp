#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#define NONE -1
#define UNVISITED 0
#define VISITED 1

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int debugging = 1;

int V = 8;
vector<vii> G;
vi low, disc, parent, vis; // DFS values used in Tarjan's Algorithm
vi AP; // Stores the articulation points
vii B; // Stores the Bridges
int children; // Count of children in tree
int t; // Time counter, Reset if doing several articulation point searches

void tarjanAPB(int u)
{
    // Initialize discovery time, low value to the time, Mark the current node as visited
    low[u] = disc[u] = ++t; vis[u] = VISITED; children = 0;
    forn (i, (int)G[u].size()) { // Go through all vertices adjacent to u
        ii v = G[u][i];
        if (vis[v.first] == UNVISITED) { // If v is not visited yet,
            children++; parent[v.first] = u;
            tarjanAPB(v.first);          // then make it a child of u in tree and recur for it
            // Check if the subtree rooted with v has a connection to one of the ancestors of u
            low[u] = min(low[u], low[v.first]);
            // u is an articulation point in following cases:
            // (1) u is root of tree and has two or more children.
            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if ((parent[u] == NONE && children > 1) || (parent[u] != NONE && disc[u] <= low[v.first]))
                AP.push_back(u);
            // If the lowest vertex reachable from subtree under v is  below u in DFS tree,
            // then u-v is a bridge
            if (low[v.first] > disc[u])
                B.push_back(ii(u, v.first));
        }
        else if (v.first != parent[u]) // Update low value of u for parent function calls.
            low[u] = min(low[u], low[v.first]);
} }

int main()
{
    FASTER;
    G.assign(V, vii());
    G[0].push_back(ii(1, 1));
    G[0].push_back(ii(2, 1));
    G[1].push_back(ii(0, 1));
	G[1].push_back(ii(2, 1));
	G[2].push_back(ii(0, 1));
	G[2].push_back(ii(1, 1));
	G[2].push_back(ii(3, 1));
	G[3].push_back(ii(2, 1));
	G[3].push_back(ii(4, 1));
	G[4].push_back(ii(3, 1));
	G[4].push_back(ii(5, 1));
	G[4].push_back(ii(6, 1));
	G[5].push_back(ii(4, 1));
	G[5].push_back(ii(6, 1));
	G[5].push_back(ii(7, 1));
	G[6].push_back(ii(4, 1));
	G[6].push_back(ii(5, 1));
	G[7].push_back(ii(5, 1));

    printf("Articulation Points & Bridges (the input graph must be UNDIRECTED)\n");
    //Initializing for Tarjan's Algorithm
    disc.assign(V, UNVISITED); low.assign(V, UNVISITED);
    parent.assign(V, NONE); vis.assign(V, UNVISITED); AP.clear(); B.clear();
    forn (i, V)
        if (vis[i] == UNVISITED)
            { t = 0; tarjanAPB(i); }

    printf("\nArticulation Points:\n");
    forn (i, (int)AP.size()) printf("%d ", AP[i]);
    printf("\nBridges:\n");
    forn (j, (int)B.size()) printf("%d to %d\n", B[j].first, B[j].second);

    return 0;
}

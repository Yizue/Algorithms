#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#define UNVISITED 0
#define VISITED 1
const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

const int debugging = 1;

int V = 8;
vector<vii> G; // List of Adjacency Lists, the pair stores the Vertex edge is connected to and the weight of edge
vi vis; // Whether Vertex i has been visited or not

// Simple DFS
void dfs(int u) {
    DEBUG printf("%d ", u);
    vis[u] = VISITED; // mark current Vertex u as visited
    forn(j, (int)G[u].size()) { // Go through the AdjList of u
        ii e = G[u][j]; // e is a (neighbor, weight) pair
        if (vis[e.first] == UNVISITED)
            dfs(e.first); // recursively visits unvisited neighbors of vertex u
} } // for simple graph traversal, we ignore the weight stored at v.second

// Simple BFS
void bfs(int s) {
    vi d(V, MAX_INT); d[s] = 0; // create dist vector, distance from source s to s is 0
    queue<int> q; q.push(s); // Create queue, push source int queue
    while (!q.empty()) {
        int u = q.front(); q.pop(); // Pop next Vertex in queue
        forn(j, (int)G[u].size()) {
            ii v = G[u][j];
            if (d[v.first] == MAX_INT) { // if v.first is unvisited + reachable
                d[v.first] = d[u]+1; // store dist from source
                q.push(v.first); // enqueue v.first for the next iteration
    } } }
    DEBUG forn(i, V) printf("%d: %d\n", i, d[i]);
}

int main()
{
    FASTER;
    G.assign(V, vii()); // assign blank vectors of pair<int, int>s to G
    vis.assign(V, UNVISITED); // assign UNVISITED for all Vertexes

    G[0].push_back(ii(1, 1));
    G[0].push_back(ii(2, 1));
    G[1].push_back(ii(3, 1));
    G[1].push_back(ii(4, 1));
    G[2].push_back(ii(3, 1));
    G[3].push_back(ii(4, 1));
    G[4].push_back(ii(0, 1));
    G[6].push_back(ii(7, 1));

    DEBUG printf("DFS:\n");
    dfs(0);
    DEBUG printf("\nBFS:\n");
    bfs(0);

    // Count Connected Components of a Graph
    int numCC = 0;
    vis.assign(V, UNVISITED); // Reset visited list
    forn (i, V) // for each vertex i in [0..V-1]
        if (vis[i] == UNVISITED) // if vertex i is not visited yet
            printf("CC %d: ", ++numCC), dfs(i), printf("\n");

    return 0;
}

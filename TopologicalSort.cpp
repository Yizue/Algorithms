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

#define UNVISITED 0
#define VISITED 1

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int debugging = 1;

int V = 8;
vector<vii> G;
vi vis; // whether G[i] has been visited or not
vi topoSort;  // global vector to store the topological sort in reverse order

void topSort(int u) {  // Recursive function used to find the topological sort of a CC
    vis[u] = VISITED;
    forn (j, (int)G[u].size()) {
        ii v = G[u][j];
        if (vis[v.first] == UNVISITED)
            topSort(v.first);
    }
    topoSort.push_back(u); }  // Stores it in reverse order

int main()
{
    FASTER;
    G.assign(V, vii());
    G[0].push_back(ii(1, 1));
    G[0].push_back(ii(2, 1));
    G[1].push_back(ii(2, 1));
    G[1].push_back(ii(3, 1));
    G[2].push_back(ii(3, 1));
    G[2].push_back(ii(4, 1));
    G[3].push_back(ii(5, 1));
    G[4].push_back(ii(3, 1));
    G[4].push_back(ii(5, 1));
    G[4].push_back(ii(7, 1));
    G[5].push_back(ii(6, 1));
    G[6].push_back(ii(7, 1));

    printf("Topological Sort (the input graph must be DAG): ");
    topoSort.clear();
    vis.assign(V, UNVISITED);
    forn (i, V)  // Topological Sort, O(V + E)
        if (vis[i] == UNVISITED)
            topSort(i);
    reverse(topoSort.begin(), topoSort.end());   // reverse topoSort
    forn (i, (int)topoSort.size()) printf(" %d", topoSort[i]);
    printf("\n");

    return 0;
}

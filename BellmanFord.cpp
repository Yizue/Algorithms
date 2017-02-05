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
bool c = false;

int V = 6;
vector<vii> G;
vi dist;

bool bellmanFord(int s) {
    dist.assign(V, INF); dist[s] = 0;
    forn (i, V - 1)  // relax all E edges V-1 times, overall O(VE)
        forn (u, V)  // these two loops = O(E)
            forn (j, (int)G[u].size()) {
                ii v = G[u][j];        // we can record SP spanning here if needed
                dist[v.first] = min(dist[v.first], dist[u] + v.second);   // relax
            }
    // Check to see if we can still relax an edge
    bool hasNegCycle = false;
    forn (u, V)
        forn (j, (int)G[u].size()) {
            ii v = G[u][j];
            if (dist[v.first] > dist[u] + v.second) // should be false
                hasNegCycle = true;     // but if true, then negative cycle exists!
        }
    return hasNegCycle;
}

int main() {
	FASTER;

	G.assign(V, vii());
    G[0].push_back(ii(1, 5));
    G[0].push_back(ii(2, 10));
	G[1].push_back(ii(2, 12));
	G[1].push_back(ii(3, 25));
	G[2].push_back(ii(1, 12));
	//G[2].push_back(ii(3, 15));
	G[2].push_back(ii(3, -16));
	G[2].push_back(ii(4, 20));
	G[3].push_back(ii(2, 15));
	//G[3].push_back(ii(2, -15));
    G[3].push_back(ii(4, 6));
	G[3].push_back(ii(5, 14));
	//G[4].push_back(ii(3, 6));
	//G[4].push_back(ii(3, -6));
	G[4].push_back(ii(5, 20));

    bool hasNegCycle = bellmanFord(0);
    printf("Negative Cycle Exist? %s\n", hasNegCycle ? "Yes" : "No");

    if (!hasNegCycle)
        forn (i, V)
            printf("SSSP from %d to %d = %d\n", 0, i, dist[i]);

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define INF 1e9

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int debugging = 1;

int V = 6;
vector<vii> G;
vi dist;

void dijk(int s) { // Dijkstra's Algorithm
    dist.assign(V, INF); dist[s] = 0;   // INF = 1B to avoid overflow
    // Sort the pairs by increasing distance from s, note that the pair here is <dist, VertexTo>
    priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
    while (!pq.empty()) {
        ii fr = pq.top(); pq.pop();     // greedy: pick shortest unvisited vertex
        int d = fr.first, u = fr.second;
        if (d > dist[u]) continue;   // Required to skip outdated pairs with longer distances
        forn (j, (int)G[u].size()) { // Check all outgoing edges from u
            ii v = G[u][j];
            if (dist[u] + v.second < dist[v.first]) { // relaxation step
                dist[v.first] = dist[u] + v.second;
                pq.push(ii(dist[v.first], v.first));
} } } } // note: this variant can cause duplicate items in the priority queue

int main()
{
    FASTER;
    G.assign(V, vii());
    G[0].push_back(ii(1, 10));
    G[0].push_back(ii(2, 15));
	G[0].push_back(ii(4, 20));
	G[1].push_back(ii(3, 15));
	G[3].push_back(ii(2, 5));
	G[3].push_back(ii(5, 5));
	G[4].push_back(ii(2, 5));
	G[4].push_back(ii(5, 15));
	dijk(0);
	forn (i, V)
        printf("SSSP from %d to %d = %d\n", 0, i, dist[i]);

    return 0;
}

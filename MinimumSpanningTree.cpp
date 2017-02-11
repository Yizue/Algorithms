#include <bits/stdc++.h>
using namespace std;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

const int debugging = 1;

// Union-Find Disjoint Sets using both path compression and union by rank heuristics
class UnionFind {
    private:
        vi p, rank, setSize;
        int numSets;
    public:
        UnionFind(int N) {
            setSize.assign(N, 1); numSets = N; rank.assign(N, 0);
            p.assign(N, 0); forn(i, N) p[i] = i; }

        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) { numSets--;
                int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) { p[y] = x; setSize[x] += setSize[y]; }
            else { p[x] = y; setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++; } } }

        int numDisjointSets() { return numSets; }
        int sizeOfSet(int i) { return setSize[findSet(i)]; }
};

vector< pair<int, ii> > Edge;  // Edge list: (weight, two vertices) of the edge
int V = 5, E = 7;

int kruskal() { // Kruskal's algorithm
    sort(Edge.begin(), Edge.end()); // sort by edge weight O(E log E)

    int mst_cost = 0;
    UnionFind UF(V);    // all V are disjoint sets initially
    forn (i, E) {   // for each edge, O(E); check if the edge would form a cycle with UF
        pair<int, ii> fr = Edge[i];
        // If the edge would not form a cycle, add the eight to the total cost of the MST
        // and link them (union)
        if (!UF.isSameSet(fr.second.first, fr.second.second)) {
            mst_cost += fr.first;
            UF.unionSet(fr.second.first, fr.second.second);
    } }
    return mst_cost;
}

//------------------------------------------------------------------------------
int _V, _E;
vector<vii> G;
vi taken;
priority_queue<ii, vii, greater<ii> > Q; // priority queue to help choose shorter edges

void process(int vtx) { // take given vertex and process all edges incident to it
    taken[vtx] = 1;
    for (int j = 0; j < (int)G[vtx].size(); j++) {
        ii v = G[vtx][j];
        if (!taken[v.first]) {
            Q.push(ii(v.first, v.second));
        }
} }
// prim's Algorithm starting on Vertex s, O(E log V)
// Warning: will only traverse connected component with s in it
int prim(int s) {
    taken.assign(_V, 0); process(s);
    int mst = 0;
    while (!Q.empty()) { // repeat until V vertexes (E=V-1 edges) are taken
        ii fr = Q.top(); Q.pop();
        if (!taken[fr.first]) { // if not taken yet, take front, process all edges incident to front
            mst += fr.second; process(fr.first);
        }
    }
    return mst;
}


int main()
{
    FASTER;
    /*
    Graph with list of weighted edges (fr, to, wei)
    V:5 E:7
    0 1 4
    0 2 4
    0 3 6
    0 4 6
    1 2 2
    2 3 8
    3 4 9
    */

    Edge.push_back(make_pair(4, ii(0, 1)));
    Edge.push_back(make_pair(4, ii(0, 2)));
    Edge.push_back(make_pair(6, ii(0, 3)));
    Edge.push_back(make_pair(6, ii(0, 4)));
    Edge.push_back(make_pair(2, ii(1, 2)));
    Edge.push_back(make_pair(8, ii(2, 3)));
    Edge.push_back(make_pair(9, ii(3, 4)));

    printf("MST cost <kruskal>: %d\n", kruskal());

    _V = 5; _E = 7;
    G.assign(_V, vii());
    G[0].push_back(ii(1, 4)); G[1].push_back(ii(0, 4));
    G[0].push_back(ii(2, 4)); G[2].push_back(ii(0, 4));
    G[0].push_back(ii(3, 6)); G[3].push_back(ii(0, 6));
    G[0].push_back(ii(4, 6)); G[4].push_back(ii(0, 6));
    G[1].push_back(ii(2, 2)); G[2].push_back(ii(1, 2));
    G[2].push_back(ii(3, 8)); G[3].push_back(ii(2, 8));
    G[3].push_back(ii(4, 9)); G[4].push_back(ii(3, 9));

    printf("MST cost <prim>: %d\n", prim(0));

    return 0;
}

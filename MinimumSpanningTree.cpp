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

    printf("MST cost = %d\n", kruskal());

    return 0;
}

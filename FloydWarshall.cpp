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

const int debugging = 1;

const int V = 6;
int G[V+5][V+5]; // Graph represented by Adj matrix
int p[V+5][V+5]; // let p be a 2D parent matrix, where p[i][j] is the last vertex before j
// on a shortest path from i to j, i.e. i -> ... -> p[i][j] -> j

void floydWarshall() { // O(V^3), can't support negative cycles
    forn (i, V) forn (j, V) p[i][j] = i; // Initialize parent matrix

    forn (k, V) // remember that loop order is k->i->j
        forn (i, V)
            forn (j, V)
                if (G[i][k] + G[k][j] < G[i][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                    p[i][j] = p[k][j];
                }
}

// Prints shortest path from i to j, do a check first on whether path exists
void pPath(int i, int j) {
    if (i != j) pPath(i, p[i][j]);
    printf("%d ", j);
}

void printPath(int i, int j)
{
    if (G[i][j] == INF) printf("Path does not exist.\n");
    else pPath(i, j);
}

int main() {
	FASTER;

    forn (i, V) { // Initialize AdjMatrix to INF except for Vertex to itself
        forn (j, V) G[i][j] = INF;
        G[i][i] = 0;
    }
    //Edges
    G[0][1]=5;
    G[0][2]=10;
    G[1][2]=12;
    G[1][3]=25;
    G[2][3]=15;
    G[2][4]=20;
    G[3][4]=6;
    G[3][5]=14;
    G[4][5]=20;

    floydWarshall();
    forn (i, V) forn (j, V) printf("APSP(%d, %d) = %d\n", i, j, G[i][j]);
    printf("\nPath (%d, %d): ", 0, 5); printPath(0, 5);
    printf("\nPath (%d, %d): ", 1, 4); printPath(1, 4);
    printf("\nPath (%d, %d): ", 1, 0); printPath(1, 0);

	return 0;
}

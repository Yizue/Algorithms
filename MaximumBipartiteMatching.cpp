#include <bits/stdc++.h>
using namespace std;

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

vector<vi> G;
vi match, vis;

// O (VE) Algorithm using Berge's Lemma for MCBM
int Aug(int l) {                 // return 1 if an augmenting path is found
  if (vis[l]) return 0;          // return 0 otherwise
  vis[l] = 1;
  forn (j, (int)G[l].size()) {
    int r = G[l][j];
    if (match[r] == -1 || Aug(match[r])) {
      match[r] = l; return 1;                           // found 1 matching
  } }
  return 0;                                                  // no matching
}
int main()
{
    FASTER;
    int V = 8, Vleft = 4;  // Vleft = size of the left set
    G.assign(V, vi());
    G[0].push_back(4);
    G[0].push_back(5);
    G[1].push_back(5);
    G[1].push_back(6);
    G[2].push_back(7);
    //G[3].push_back(6);
    G[3].push_back(7);

    int MCBM = 0;
    match.assign(V, -1);
    forn (l, Vleft) {
        vis.assign(Vleft, 0);  // reset before each recursion
        MCBM += Aug(l);
    }
    printf("Found %d matchings\n", MCBM);

    return 0;
}

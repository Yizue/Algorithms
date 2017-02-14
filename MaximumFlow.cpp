#include <bits/stdc++.h>
using namespace std;

const int INF = 1.0e9;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define forn(i,n) for(int (i) = 0; (i) < (n); ++(i))
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); ++(i))
#define formn(i,m,n) for(int (i) = (m); (i) > (n); --(i))

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;

int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}
int lcm(int a,int b){return a*(b/gcd(a,b));}

//----------------------------------------------------------------------//

class Edge{
    public:
        int u,v,cap,f;

        Edge(int _u, int _v, int _cap) : u(_u),v(_v),cap(_cap){ f = 0; }

        int other(int vertex){
            if(vertex == u)return v;
            else if(vertex == v)return u;
            return -1;
        }
        int residualTo(int vertex){
            if(vertex == u)return f;
            return cap - f;
        }
        void addFlowTo(int vertex, int ff){
            if(vertex == u) f -= ff;
            else if(vertex == v) f += ff;
        }
};

typedef vector<Edge*> edgeList;

#define MAX_V 1000
#define MAX_E 1000
const int SRC = 0;
const int SINK = 1;
int flow;
edgeList parent;
vi visited;
vector<edgeList> G;

void addEdge(int u, int v, int cap){
	Edge* e = new Edge(u,v,cap);
	G[u].push_back(e); // Pass same edge object to u and v lists
	G[v].push_back(e);
}

bool augmentingPath(){
	queue<int> q; q.push(SRC);
	forn (i, MAX_V) parent.push_back(NULL);
	visited.assign(MAX_V, 0); visited[SRC] = 1;
	while(!q.empty()){ // BFS - find existing path and store it
		int u = q.front(); q.pop();
		if(u == SINK) break;
		forn (i, (int)G[u].size()) {
			Edge* e = G[u][i];
			int v = e->other(u);
			if(!visited[v] && e->residualTo(v) > 0){
				visited[v]=1;
				parent[v]=e;
				q.push(v);
			}
		}
	}
	return visited[SINK]; // Found path to the Sink
}

// Edmonds-Karp Algorithm O(V^2 E)
int maxFlow(){
	int mf = 0;
	while(augmentingPath()){
		flow = INF;
		for(int v=SINK; v!=SRC ; v=parent[v]->other(v)){ // Find min flow in path
			flow = min(flow, parent[v]->residualTo(v));
		}
		for(int v=SINK; v!=SRC ; v=parent[v]->other(v)){
			parent[v]->addFlowTo(v,flow);
		}
		mf+=flow;
	}
	return mf;
}


void data1();

int main(){
    FASTER;

    G.assign(MAX_V, edgeList());
	addEdge(SRC,2,2);
	addEdge(SRC,3,3);
	addEdge(2,4,5);
	addEdge(2,5,1);
	addEdge(4,SINK,1);
	addEdge(5,SINK,1);
	addEdge(3,SINK,2);
    assert(maxFlow() == 4);
    printf("All test passed\n");

    return 0;
}

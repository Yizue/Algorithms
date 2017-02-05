#include <bits/stdc++.h>
using namespace std;

const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();
const int INF = 1.0e9;
const int NEG_INF = -1.0e9;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define PI acos(0)*2.0
#define eps 1.0e-9
#define are_equal(a,b)fabs(a-b)<eps
#define LS(b)(b& (-b)) // Least significant bit
#define DEG_to_RAD(a)((a*PI)/180.0) // convert to radians

#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<int,char> ic;
typedef pair<long,char> lc;
typedef pair<double,double> dd;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<dd> vdd;


int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}
int lcm(int a,int b){return a*(b/gcd(a,b));}
int cmp(const void *a, const void *b) {return *(int*)a - *(int*)b;}

const int debugging = 1;

/*
	__builtin_popcount(int d) // count bits
	__builtin_popcountll(long long d)
	strtol(s, &end, base); // convert base number
*/
//----------------------------------------------------------------------//

const int N = 1000;
int prime[N+1]; // Ind corresponds to the prime number
// Finds all the prime numbers smaller than N - O( N log (log N) )
void sieveEratos(){
    MEM(prime, 1);
    for(int p=2; p*p<=N; p++)
        if(prime[p]) // If p is still prime
            for (int i=p*2; i<=N; i+=p)// Update all multiples of p as not prime
                prime[i]=0;
}

const int M = 10;
ll catalanNum[M];
// Generates N Catalan Numbers
void catalanNumbers() {
	catalanNum[0] = 1;
	fornm (i,1,M)
		catalanNum[i] = (((2*i)*(2*i-1))*catalanNum[i-1])/((i+1)*i);
}

const int Q = 30;
ll fibs[Q+1];

// Generates Nth Fibonacci Numbers - O (n)
ll fib(int n)
{
    fibs[0] = 0; fibs[1] = 1;
    fornm (i,2,n+1) fibs[i] = fibs[i-1] + fibs[i-2];
    return fibs[n];
}

int main() {
	FASTER;
	// Prime numbers
	sieveEratos();
	cout << "Primes up to " << N << ": " << endl;
	forn(i, N) if (prime[i]) cout << i << " "; cout << endl;

    // Catalan Numbers
    catalanNumbers();
    cout << "Catalan Numbers up to" << N << ": " << endl;
	forn(j, M) cout << catalanNum[j] << " "; cout << endl;

	// Fibonacci Numbers
    cout << Q << "th Fibonacci Number: " << fib(Q-1) << endl;

	return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int INF = 1.0e9;

#define MEM(arr,val)memset(arr,val, sizeof arr)
#define PI acos(0)*2.0
#define eps 1.0e-9
#define are_equal(a,b)fabs(a-b)<eps
#define DEG_to_RAD(a)((a*PI)/180.0) // convert to radians

#define forn(i,n) for(int (i) = 0; (i) < (n); (i)++)
#define fornm(i,n,m) for(int (i) = (n); (i) < (m); (i)++)
#define formn(i,m,n) for(int (i) = (m); (i) > (n); (i)--)
#define DEBUG if(debugging)

#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

typedef long long ll;

int gcd(int a,int b){return b == 0 ? a : gcd(b,a%b);}
int lcm(int a,int b){return a*(b/gcd(a,b));}
int cmp(const void *a, const void *b) {return *(int*)a - *(int*)b;}

const int debugging = 1;
//----------------------------------------------------------------------//

// Operators:
// & AND
// | OR
// ^ XOR
// n << m L-shift n by m
// n >> m R-shift n by m
// All of these can be paired with = for assignment

// Least significant bit
int LSB (unsigned v) {int r=0, n=1; while(1) {if(v&n) return r; else {r++; n<<=1;}}}
// Most significant bit
int MSB (unsigned v) {int r=0; while(v >>= 1) r++; return r;}

const int N = 8;
int b[N];
// Int to Binary as Array
void bin(unsigned n)
{
    for (unsigned i = 1 << N-1, j=0; i>0; i/=2, j++) (n & i)? b[j]=1 : b[j]=0;
}

int main() {
	FASTER;

    bin(30);
	forn (i, N) cout << b[i]; cout << endl;

    cout << "LSB of " << 30 << ": " << LSB(4) << endl;
	cout << "MSB of " << 30 << ": " << MSB(30) << endl;

	return 0;
}

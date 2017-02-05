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

// Left Turn Test - returns 1 if a left turn was made from going from p to r, -1 if right turn
// 0 if co-linear
bool leftTurnTest(dd p, dd q, dd r)
{
    dd pq = dd(q.first-p.first, q.second-p.second), qr = dd(r.first-q.first, r.second-q.second);
    if (pq.first*qr.second - pq.second*qr.first > 0) return 1;
    else if (pq.first*qr.second - pq.second*qr.first < 0) return -1;
    else return 0;
}

// Determine if two line segments p1p2 and q1q2 intersect - uses left turn test
bool doSgmtIntersect(dd p1, dd q1, dd p2, dd q2)
{
    return ((leftTurnTest(p1, q1, p2) != leftTurnTest(p1, q1, q2))
         && (leftTurnTest(p2, q2, p1) != leftTurnTest(p2, q2, q1)));
}

// Area of Triangle - Uses the determinant method
double areaTriangle(dd p, dd q, dd r)
{
    return fabs(0.5*(p.first*q.second+q.first*r.second+r.first*p.second
                     -r.first*q.second-p.first*r.second-q.first*p.second));
}
// Area of convex polygon - sum of constituent triangle area method
// the points must be given in clockwise or ccwise order, area will be positive if ccwise order
// negative otherwise
double areaPolygon(vdd pts)
{
    double area = 0.0;
    forn(i, pts.size()-1)
        area += (pts[i].first*pts[i+1].second - pts[i].second*pts[i+1].first);
    return (area + pts[pts.size()-1].first*pts[0].second - pts[pts.size()-1].second*pts[0].first)*0.5;
}

// Test for whether a point is inside the polygon (true) or out side, uses left-turn test
// on every edge of polygon
bool ifInsidePolygon(dd pt, vdd polygon)
{
    forn(i, polygon.size()-1)
        if (leftTurnTest(pt, polygon[i], polygon[i+1]) < 0) return false;
    if (leftTurnTest(pt, polygon[polygon.size()-1], polygon[0]) < 0) return false;
    return true;
}

// Convex Hull - the minimum area needed to enclose a set of points in a convex polygon
// Uses Graham Scan Method O (n log n):
vdd convexHull(vdd setPts)
{
    vdd cvHull;
    // Step 1: Get the lowest point (y-val) and set as the anchor of convex hull
    dd minY = setPts[0];
    fornm(i,1,setPts.size()) if(minY.second > setPts[i].second) minY = setPts;
    cvHull.push_back(minY);
    // Step 2: TODO
}


int main() {
	FASTER;
    // Left Turn Test
    dd p = dd(3, 4), q = dd(0, 2), r = dd(0, -2);
    cout << leftTurnTest(p,q,r) << endl;
    // Segment Intersection Test
    dd p1 = dd(0, 0), q1 = dd(2, 1), p2 = dd(-1, 2), q2 = dd(2, 2);
    cout << doSgmtIntersect(p1,q1,p2,q2) << endl;
    // Area of Triangle
    dd a = dd(-7.31, -5.32), b = dd(4.12, 0.23), c = dd(-2.27, 2.85);
    cout << areaTriangle(a,b,c) << endl; // 32.7056
    // Area of Convex Polygon
    vdd pts;
    pts.push_back(dd(-8.0, 0.0));
    pts.push_back(dd(0.0, 8.0));
    pts.push_back(dd(8.0, 0.0));
    pts.push_back(dd(0.0, -8.0));
    cout << areaPolygon(pts) << endl; // -128
    // test for inclusion
    vdd pts2;
    pts2.push_back(dd(0.0, -8.0));
    pts2.push_back(dd(8.0, 0.0));
    pts2.push_back(dd(0.0, 8.0));
    pts2.push_back(dd(-8.0, 0.0));
    dd pt = dd(0.0, -8.0);
    cout << ifInsidePolygon(pt, pts2) << endl;


	return 0;
}

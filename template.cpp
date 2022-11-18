#include <bits/stdc++.h>
using namespace std;

//note: lsb_set==lsb && lsb_unset==lsbu
//just take log2(lsb_set(x)) if want just pos. //x!=0
int log2_floor(long long i) {
    return i ? __builtin_clzll(1ll) - __builtin_clzll(i) : -1;
}
#define lsb(x) (x&-x)
#define lsbu(x) (x&(x+1))
#define msb(x) __lg(x)
#define msbu(x)


//order_of_key(k) :Number of items strictly smaller than k.
//find_by_order : K-th smallest element.
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define ordered_set_pair tree<pair<int,int>, null_type, less<pair<int, int>>, rb_tree_tag,tree_order_statistics_node_update>

typedef tree<int , null_type ,  less_equal<int> , rb_tree_tag , tree_order_statistics_node_update> ordered_multiset;

template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// cout << (o_set.find_by_order(0)) ->first<<" "<<(o_set.find_by_order(0)) ->second<<"\n";
// cout << o_set.order_of_key({4,3})<<"\n";
struct comp { //for ordered_set, sorts based on only first element & uniqueness also based on only first element
	bool operator() (const pair <int , int> &a, const pair <int , int> &b) const {
		return a.first < b.first;
	}
};


#define INF 1e9+9
int nmax() {return -1 * INF;}
template<typename Arg, typename... Args>
int nmax(Arg a, Args... args) { return std::max(a, nmax(args...)); }

int nmin() {return INF;}
template<typename Arg, typename... Args>
int nmin(Arg a, Args... args) { return std::min(a, nmin(args...)); }


void ans22(bool x) {if (x) cout << "YES" << endl; else cout << "NO" << endl;}


// Given three collinear points p, q, r, the function checks if point q lies on line segment 'pr'
bool onsegment(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
	if (q.first <= max(p.second, r.first) && q.first >= min(p.first, r.first) &&
	        q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).  // The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r)
{
	int val = (q.second - p.second) * (r.first - q.first) -
	          (q.first - p.first) * (r.second - q.second);

	if (val == 0) return 0;  // collinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}



#define dsu(n) parent_dsu.resize(n);rank_dsu.resize(n,0);iota(parent_dsu.begin(),parent_dsu.end(),0)
vector<int> parent_dsu, rank_dsu;
void make_set_dsu(int v) {
	parent_dsu[v] = v;  //initially all elements of parent_dsu = same value // so no need of make_set_dsu !!
	rank_dsu[v] = 0;     //initially all elemnts of rank = 0
}

int find_set_dsu(int v) {
	if (v == parent_dsu[v])
		return v;
	return parent_dsu[v] = find_set_dsu(parent_dsu[v]); //path compression
	//O(logn) avg, but while building tree by doing union itself everything happens, and it becomes O(logn) after construction, for any call.
}

void union_sets_dsu(int a, int b) {
	a = find_set_dsu(a);
	b = find_set_dsu(b);
	if (a != b) {
		if (rank_dsu[a] < rank_dsu[b])
			swap(a, b);
		parent_dsu[b] = a;
		if (rank_dsu[a] == rank_dsu[b])
			rank_dsu[a]++;
	}
}

struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};



void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
void __print(const vector<int>& x) {int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}


template<typename T>void __print(stack<T> st) {while (!st.empty()) {cerr << st.top() << " "; st.pop();};}
template<typename T>void __print(queue<T> st) {while (!st.empty()) {cerr << st.front() << " "; st.pop();};}
template<typename T>void __print(deque<T> st) {while (!st.empty()) {cerr << st.front() << " "; st.pop_front();};}


void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}


/*------------time--------------*/
double __start_time = 0;
void __stime() {
	__start_time = 1.0 * clock() / CLOCKS_PER_SEC;
}

void __etime() {
#ifndef ONLINE_JUDGE
	cerr << "Time elapsed: " << (1.0 * clock() / CLOCKS_PER_SEC - __start_time) << " s.\n";
#endif
}
/*------------time--------------*/


long long ccccc = 0;
#ifndef ONLINE_JUDGE
#define tle ccccc++;assert(ccccc<1e7)
#define wd(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define tle
#define wd(x...)
#endif


// #define int long long
/*------------shortcuts----------*/
#define fio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define unique(a) (a).erase(std::unique((a).begin(),(a).end()),(a).end())
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define vil vector<long long>
#define vii vector<pair<int,int>>
#define viil vector<pair<long long,long long>>
#define si set<int>
/*------------shortcuts----------*/

void print(auto &arr) {
	for (int i = 0; i < arr.size(); i++)
		printf("%d ", arr[i]);
	printf("\n");
}

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
long long mod = 1e9 + 7;


int32_t main() {
	// your code goes here
//fio;
//dsu(n);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
#endif

//__stime();

	int t;
	scanf("%d", &t);

	while (t--) {
		int n;
		scanf("%d", &n);
		vector<int> arr(n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
		}


//    printf("YES\n");
//    printf("NO\n");
		// printf("%d\n", ans);
	}

//__etime();

	return 0;
}

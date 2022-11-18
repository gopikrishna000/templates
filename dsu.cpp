
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

/*
note: if a,b is a relation, then need to add a,b and also -a,-b (ie:a+N,b+N)
note: using same dsu for this also, just size is 2N;
note: if a,b is relation, then first check whether a,b+N||a+N,b already exist in same tree, if so then *false*, else *true*...
(may be already same relation exist, or new relation is created by union.)
And the false case is always executed before calling union, by just manually checking... and if called union function, then it always means return value is true.
*/

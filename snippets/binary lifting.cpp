<snippet>
	<content><![CDATA[

int n, l;  //upd n
vector<vector<int>> adj; //upd adj
int _q = 0; //update it to _q if wt ed tree is used
vector<vector<pair<int, int>>> wadj;
vector<int> wt;

int timer;
vector<int> tin, tout, depth;
vector<vector<int>> up;

void dfs(int v, int p, int dep) //depth is extra,in case needed...
{
	tin[v] = ++timer;
	up[v][0] = p;
	depth[v] = dep;
	for (int i = 1; i <= l; ++i)
		up[v][i] = up[up[v][i - 1]][i - 1];

	for (int u : adj[v]) {
		if (u != p)
			dfs(u, v, dep + 1);
	}

	tout[v] = ++timer;
}

void wdfs(int v, int p, int sofar)
{
	wt[v] = sofar;
	for (auto &[u, w] : wadj[v]) {
		if (u != p)
			wdfs(u, v, sofar + w);
	}
}

bool is_ancestor(int u, int v)
{
	return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
	if (is_ancestor(u, v))
		return u;
	if (is_ancestor(v, u))
		return v;
	for (int i = l; i >= 0; --i) {
		if (!is_ancestor(up[u][i], v))
			u = up[u][i];
	}
	return up[u][0];
}

int distance(int u, int v) {
	int anc = lca(u, v);
	return abs(depth[u] - depth[anc]) + abs(depth[anc] - depth[v]);
}

int weight(int u, int v) {
	int anc = lca(u, v);
	return abs(wt[u] - wt[anc]) + abs(wt[anc] - wt[v]);
}

void preprocess(int root) {
	tin.resize(n);
	tout.resize(n);
	depth.resize(n);
	timer = 0;
	l = ceil(log2(n));
	up.assign(n, vector<int>(l + 1));
	dfs(root, root, 0);
	if(_q){
		wt.resize(n);
		wdfs(root,root,0);
	}
}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>binary lifting</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

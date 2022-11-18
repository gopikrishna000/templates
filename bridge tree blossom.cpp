
vector<vector<int>> adj; // upd adj
set<pair<int, int>> bridge_set;
void IS_BRIDGE(int u, int v) {
	//this is called if edge u to v forms a bridge, do whatever you want
	bridge_set.insert({u, v});
	bridge_set.insert({v, u});
}

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfsa(int v, int p = -1) {
	visited[v] = true;
	tin[v] = low[v] = timer++;
	for (int to : adj[v]) {
		if (to == p) continue;
		if (visited[to]) {
			low[v] = min(low[v], tin[to]);
		} else {
			dfsa(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] > tin[v])
				IS_BRIDGE(v, to);
		}
	}
}

void find_bridges(int n) {
	timer = 0;
	visited.assign(n, false);
	tin.assign(n, -1);
	low.assign(n, -1);
	for (int i = 0; i < n; ++i) {
		if (!visited[i])
			dfsa(i);
	}
}

vector<int> id;
vector<int> vis;
void dfsb(int node, int component_number) {
	id[node] = component_number ;
	vis[node] = true;
	for (auto &x : adj[node]) {
		//note extra O(logn) factor due to bridge set.
		if (!vis[x] && (bridge_set.find({node, x}) == bridge_set.end())) {
			int next = x;
			dfsb(next, component_number);
		}
	}
}

void blossom(int n) {
	vis.assign(n, 0);
	id.assign(n, 0);
	iota(all(id), 0);
	// int unique_component_number = 0;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			dfsb(i, i);
			// unique_component_number++;
		}
	}
}

vector<vector<int>> bridge_tree;
void bridge_tree_build(int n) {
	find_bridges(n);
	blossom(n);

	vector<vector<int>> &arr = bridge_tree;
	arr.assign(n, vector<int>());
	for (auto &[a, b] : bridge_set) {
		if (id[a] == id[b])
			continue;
		arr[id[a]].push_back(id[b]);
	}
}


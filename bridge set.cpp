
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

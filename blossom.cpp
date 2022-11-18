
vector<int> component;
vector<int> vis;
void dfsb(int node, int component_number) {
	component[node] = component_number ;
	vis[node] = true; 
	for (auto &x : adj[node]) {
		if (!vis[x] && (bridge_set.find({node, x}) == bridge_set.end())) {
			int next = x;
			dfsb(next, component_number);
		}
	}
}

void blossom(int n) {
	vis.assign(n, 0);
	component.assign(n,0);
	iota(all(component),0);
	// int unique_component_number = 0;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			dfsb(i, i);
			// unique_component_number++;
		}
	}
}


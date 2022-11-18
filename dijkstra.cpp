

long long INFD = 1e16+7;
vector<vector<pair<int, int>>> adj;
//p stores parent array for each noed //d[i] stores shortest distance of i from 0
void dijkstra(int s, vector<int> & d, vector<int> & p) {
	int n = adj.size();
	d.assign(n, INFD);
	p.assign(n, -1);

	d[s] = 0;
	// using pii = pair<int, int>;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, s});
	while (!q.empty()) {
		int v = q.top().second;
		int d_v = q.top().first;
		q.pop();
		if (d_v != d[v])
			continue;

		for (auto edge : adj[v]) {
			int to = edge.first;
			int len = edge.second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
				q.push({d[to], to});
			}
		}
	}
}


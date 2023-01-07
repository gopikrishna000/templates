<snippet>
	<content><![CDATA[

int diam = 0;
const int MAXM = 1e6 + 7;
int height[MAXM];
void diameter (int vertex, int parent) {
	height[vertex] = 0;
	for (int nxt : bridge_tree[vertex]) {
		if (nxt != parent) {
			diameter(nxt, vertex);

			diam = max(diam, height[nxt] + height[vertex] + 1);
			height[vertex] = max(height[nxt] + 1, height[vertex]);
		}
	}
}


]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>diameter of tree</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

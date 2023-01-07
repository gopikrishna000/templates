<snippet>
	<content><![CDATA[

	vector<vector<int>> divisors(N + 1);
	for (int i = 1; i <= N; i++) {
		for (int j = i; j <= N; j+=i) {
			divisors[j].push_back(i);
		}
	}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>divisors</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

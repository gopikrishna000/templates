<snippet>
	<content><![CDATA[

int sumofgcd(vector<int> &arr) { // in O(n.d)
	int n = arr.size();
	vector<int> D;
	for (int i = 0; i < n; i++) {
		for (auto &d : divisors[arr[i]]) {
			D.push_back(d);
			freq[d]++;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (auto &d : divisors[arr[i]]) {
			ans += freq[d] * phi[d];
		}
	}
	for (auto &x : D)
		freq[x] = 0;
	/* 
	//If need only for i<j pairs 
	for (int i = 0; i < n; i++) {
		ans -= arr[i];
	}
	ans /= 2;
	*/
	return ans;
}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>sum of gcd of all pair of array</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

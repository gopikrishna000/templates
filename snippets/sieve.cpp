<snippet>
	<content><![CDATA[

vector<bool> is_prime(n + 1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i <= n; i++) {
	if (is_prime[i] && (long long)i * i <= n) {
		for (int j = i * i; j <= n; j += i)
			is_prime[j] = false;
	}
}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>sieve of eratosthenes</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

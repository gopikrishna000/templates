<snippet>
	<content><![CDATA[

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::shuffle(ord.begin(), ord.end(), rng);

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>random mt19937_64</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

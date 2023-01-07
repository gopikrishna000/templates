<snippet>
	<content><![CDATA[
	
int extended_euclidean(int a, int b, int *x, int *y)
{
	if (a == 0) {
		*x = 0; *y = 1;
		return b;
	}
	int x1, y1;
	int gcd = extended_euclidean(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}

int inverse(int a, int m) {
	int x, y;
	int g = extended_euclidean(a, m, &x, &y);
	if (g != 1) {
		return -1;
	}
	else {
		x = (x % m + m) % m;
		return x;
	}
}
]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>inverse</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

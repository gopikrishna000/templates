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

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>extended euclidean</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

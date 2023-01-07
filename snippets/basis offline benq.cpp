<snippet>
	<content><![CDATA[
		
vector<int> gaussianEliminationMod2(vector<int> v, int B=30) {
	int n = v.size();
	vector<int> t(B, 0);
	int used = 0;
	for(int j = B - 1; j >= 0; j --) {
		int i = used;
		while(i < n && (~v[i] >> j & 1)) i ++;
		if(i < n) {
			int x = v[i];
			swap(v[i], v[used ++]);
			t[j] = x;
			for(i = used; i < n; i ++)
				if(v[i] >> j & 1)
					v[i] ^= x;
		}
	}
	return t;
}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>basis offline</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

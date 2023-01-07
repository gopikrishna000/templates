<snippet>
	<content><![CDATA[
Hello, ${1:this} is a ${2:snippet}.
void transpose(vector<vector<int> > &b)
{
	if (b.size() == 0)
		return;

	vector<vector<int> > trans_vec(b[0].size(), vector<int>());

	for (int i = 0; i < b.size(); i++)
	{
		for (int j = 0; j < b[i].size(); j++)
		{
			trans_vec[j].push_back(b[i][j]);
		}
	}

	b = trans_vec;    // <--- reassign here
}

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>transpose of 2d matrix</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

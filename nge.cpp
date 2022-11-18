
vector<int> pse, pge, nge, nse, nsee, pge1;
void preprocess(vector<int> &arr) {
	int n = arr.size();
	pse.resize(n), pge.resize(n), nge.resize(n), nse.resize(n), nsee.resize(n), pge1.resize(n);

	//previous greater (including current element)
	//ie: if for given i, maximum range [x,i-1] such that min(x,i)=arr[i], then:pge[i]=x-1.
	{
		stack<int> st;
		for (int i = 0; i < n; i++) {
			while (!st.empty() && arr[st.top()] <= arr[i])
				st.pop();

			pge[i] = (st.empty() ? -1 : st.top());
			st.push(i);
		}
	}

	//nge //next greater element, in range [i+1,n-1]
	{
		stack<int> st;
		for (int i = n - 1; i >= 0; i--) {
			while (!st.empty() && arr[st.top()] <= arr[i])
				st.pop();

			nge[i] = (st.empty() ? n : st.top());
			st.push(i);
		}
	}

	//pse //prev smaller element
	{
		stack<int> st;
		for (int i = 0; i < n; i++) {
			while (!st.empty() && arr[st.top()] >= arr[i])
				st.pop();

			pse[i] = (st.empty() ? -1 : st.top());
			st.push(i);
		}
	}

	//nse //next smaller element
	{
		stack<int> st;
		for (int i = n - 1; i >= 0; i--) {
			while (!st.empty() && arr[st.top()] >= arr[i])
				st.pop();

			nse[i] = (st.empty() ? n  : st.top());
			st.push(i);
		}
	}

	//next smaller than or equal element in range [i+1,n-1]
	{
		stack<int> st;
		for (int i = n - 1; i >= 0; i--) {
			while (!st.empty() && arr[st.top()] > arr[i])
				st.pop();

			nsee[i] = (st.empty() ? n : st.top());
			st.push(i);
		}
	}

	//previous greater element plus 1
	//meaning that pse1[i]=x => min[x,i]=i but not x-1.
	{
		stack<int> st;
		for (int i = 0; i < n; i++) {
			while (!st.empty() && arr[st.top()] < arr[i])
				st.pop();

			pge1[i] = (st.empty() ? 0 : st.top() + 1);
			st.push(i);
		}
	}
}




const int K = 25;
const int MAXN = 5e5 + 7;
int lg[MAXN + 1];
int st1[K + 1][MAXN];
int st2[K + 1][MAXN];


int rmin(int L, int R) {
	int j = lg[R - L + 1];
	return min(st1[j][L], st1[j][R - (1 << j) + 1]);
}

int rmax(int L, int R) {
	int j = lg[R - L + 1];
	return max(st2[j][L], st2[j][R - (1 << j) + 1]);
}

void sparse_table(vector<int> &arr) {
    int n = arr.size();
	lg[1] = 0;
	for (int i = 2; i <= MAXN; i++)
		lg[i] = lg[i / 2] + 1;

	std::copy(arr.begin(), arr.end(), st1[0]);
	std::copy(arr.begin(), arr.end(), st2[0]);

	for (int j = 1; j <= K; j++)
		for (int i = 0; i + (1 << j) <= n; i++)
			st1[j][i] = min(st1[j - 1][i], st1[j - 1][i + (1 << (j - 1))]);


	for (int j = 1; j <= K; j++)
		for (int i = 0; i + (1 << j) <= n; i++)
			st2[j][i] = max(st2[j - 1][i], st2[j - 1][i + (1 << (j - 1))]);
}




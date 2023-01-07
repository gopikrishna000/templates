<snippet>
	<content><![CDATA[

//Binary Trie
struct node {
	node *eks[2];
	node() {
		eks[0] = nullptr;
		eks[1] = nullptr;
	}
}*root;

//b array for undo feature // u can just set for[y, z]:b => z->eks[y] = nullptr;
void add(node *tree, int ind, auto &b) {
	if (ind == 33) return;
	int x = num[ind];
	if (!tree->eks[x]) {
		b.pb({x, tree});
		tree->eks[x] = new node();
	}
	add(tree->eks[x], ind + 1, b);
}

//binary rep into num array 33 bit.
void add_to_num(long long f) {
	num.clear();
	while (f > 0) {
		num.push_back(f % 2);
		f /= 2;
	}
	while (num.size() < 33)
		num.push_back(0);
	reverse(num.begin(), num.end());
}

void get(node *tree, int ind) {
	if (ind == 33) return;
	int x = num[ind];
	//cout<<x<<" ";
	if (!tree->eks[1 - x]) {
		get(tree->eks[x], ind + 1);
	}
	else {
		cmon += (1LL << (long long)(32 - ind));
		get(tree->eks[1 - x], ind + 1);
	}
}
/*
	root = new node();
	add_to_num(1);add(root, 0);
	add_to_num(3);add(root, 0);

	add_to_num(7);get(root, 0);
	wd(cmon^7); //cmon contains the result, ie:maxm xor value possible when 7
	//is xor-ed with any element of trie.. so cmon^7 will show that optimal element itself.
*/

]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>trie xor</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>

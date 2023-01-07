<snippet>
	<content><![CDATA[



/*----------------------changable--------------------------*/

int _p = 0; //update this global variable before querying to switch the structure.
int __nn = 1; //# of segment tree needed
// vector<int> NEUTRAL_DELTA(__nn, 0);

struct Vertex {
	int val;
	int lazy;
	Vertex() {
		//constructor neutral node
		if (_p == 0) {
			val = 0;
			lazy = 0;
		}
	}
};

//vector<Vertex> NEUTRAL_NODE(__nn, Vertex());


//search "setVertex" to find positions of setting node.
vector<vector<Vertex>> t(__nn, vector<Vertex>(4 * (1e6 + 5)));

Vertex merge(Vertex left, Vertex right) {
	if (_p == 0) {
		Vertex cur;
		cur.val = left.val + right.val;
		return cur;
	}
	else {
		Vertex cur;
		cur.val = left.val + right.val;
		return cur;
	}
}

int joinDeltas(int oldDelta, int newDelta) {
	if (_p == 0) {
		return oldDelta + newDelta;
	}
	else if (_p == 1) { //for range assignment update//also add if(t[_p][v].lazy!=NEUTRAL_DELTA) in push
		return newDelta;
	}
}

int joinValueWithDelta(int value, int delta, int length) {
	if (_p == 0) {
		return value + length * delta;
	}
	else if (_p == 1) { //for range assignment update
		return (length) * delta;
	}
}

/*----------------------changable--------------------------*/

//build(arr,1,0,n-1);
void build(auto &a, int v, int tl, int tr) {

	if (tl == tr) {//setVertex
		if (_p == 0) {
			t[_p][v].val = a[tl];
		}
		else {
			t[_p][v].val = a[tl];
		}
	}//endsetVertex
	else {
		int tm = (tl + tr) / 2;
		build(a, v * 2, tl, tm);
		build(a, v * 2 + 1, tm + 1, tr);
		t[_p][v] = merge(t[_p][v * 2] , t[_p][v * 2 + 1]);
	}
}


//sum(1,0,n-1,l,r); //tl,tr are seg range(standard:fixed for vertex v); l,r are actual range needed.
Vertex sum(int v , int tl , int tr , int l, int r) {
	if (l > r)
		return Vertex();  //return NEUTRAL_NODE[_p];
	if (l == tl && r == tr) {
		return t[_p][v];
	}
	int tm = (tl + tr) / 2;
	return merge(sum(v * 2, tl, tm, l, min(r, tm))
	             , sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

//update(1,0,n-1,pos,val); //0-based
void update(int v , int tl , int tr , int pos, int new_val) {
	if (tl == tr) {//setVertex
		t[_p][v].val = new_val; //the actual pos node
	}//endsetVertex
	else {
		int tm = (tl + tr) / 2;
		if (pos <= tm)
			update(v * 2, tl, tm, pos, new_val);
		else
			update(v * 2 + 1, tm + 1, tr, pos, new_val);
		t[_p][v] = merge(t[_p][v * 2] , t[_p][v * 2 + 1]);
	}
}

/*shortcuts*/
vi _nn(__nn);
//build(arr);
void build(auto &arr) {
	if (_p + 1 > _nn.size()) {
		t.pb(vector<Vertex>(4 * ((int)arr.size())));
		_nn.pb((int)arr.size());
	} else
		_nn[_p] = (int)arr.size();
	__nn = _nn.size();
	build(arr, 1, 0, _nn[_p] - 1);
}

//sum(l,r);
Vertex sum(int l, int r) {
	return sum(1, 0, _nn[_p] - 1, l, r);
}
//update(pos,val);
void update(int pos, int val) {
	update(1, 0, _nn[_p] - 1, pos, val);
}
/*shortcuts*/

/*--------here-comes-range-update--------------*/

void push(int v, int tl, int tr) { //setVertex
	if (_p == 0) {
		int tm = (tl + tr) / 2;
		t[_p][v * 2].val = joinValueWithDelta(t[_p][v * 2].val, t[_p][v].lazy , (tm - tl + 1));
		t[_p][v * 2].lazy = joinDeltas(t[_p][v * 2].lazy, t[_p][v].lazy);
		t[_p][v * 2 + 1].val = joinValueWithDelta(t[_p][v * 2 + 1].val, t[_p][v].lazy, (tr - tm));
		t[_p][v * 2 + 1].lazy = joinDeltas(t[_p][v * 2 + 1].lazy, t[_p][v].lazy);
		t[_p][v].lazy = 0;
	}
	else if (_p == 1) {

	}
}//endsetVertex

void update(int v, int tl, int tr, int l, int r, auto addend) {
	if (l > r)
		return;
	if (l == tl && tr == r) {//setVertex
		t[_p][v].val += (tr - tl + 1) * addend;
		t[_p][v].lazy += addend;
	}//endsetVertex
	else {
		int tm = (tl + tr) / 2;
		push(v, tl, tr);
		update(v * 2, tl, tm, l, min(r, tm), addend);
		update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
		t[_p][v] = merge(t[_p][v * 2] , t[_p][v * 2 + 1]);
	}
}

Vertex query(int v, int tl, int tr, int l, int r) {
	if (l > r)
		return Vertex();   //return NEUTRAL_NODE[_p];
	if (l <= tl && tr <= r)
		return t[_p][v];
	int tm = (tl + tr) / 2;
	push(v, tl, tr);
	return merge(query(v * 2, tl, tm, l, min(r, tm)) ,
	             query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}


//shortcut
void update(int l, int r, auto val) {
	update(1, 0 , _nn[_p] - 1, l, r, val);
}
Vertex query(int l, int r) {
	return query(1, 0, _nn[_p] - 1, l, r);
}

/*--------here-ends-range-update--------------*/




]]></content>
	<!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
	<tabTrigger>segment tree()</tabTrigger>
	<!-- Optional: Set a scope to limit where the snippet will trigger -->
	<scope>source.c++</scope>
</snippet>


/* randamized  implicit treap*/
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

// specific code
const int MAXN = 200000;

const int NEUTRAL_VALUE = INT_MIN;
const int NEUTRAL_DELTA = 0;

int joinValues(int leftValue, int rightValue) {
  return max(leftValue, rightValue);
}

int joinDeltas(int oldDelta, int newDelta) {
  return oldDelta + newDelta;
}

int joinValueWithDelta(int value, int delta, int length) {
  return value + delta;
}

// generic code
struct treap {
  int nodeValue;
  int subTreeValue;
  int delta;
  int count;
  int prio;
  bool rev;
  treap *l;
  treap *r;
};

treap nodes[MAXN];
int nodes_cnt;
vector<int> rnd;

static int getCount(treap* root) {
  return root ? root->count : 0;
}

static int getSubTreeValue(treap* root) { //for range query change accordingly //just update neutral val
  return root ? root->subTreeValue : NEUTRAL_VALUE;
}

//for range query change accordingly //just update joinval
void update(treap *root) { //subtree val update based on left and right child assuming those already updated.
  if (!root) return;
  root->subTreeValue = joinValues(joinValues(getSubTreeValue(root->l), root->nodeValue), getSubTreeValue(root->r));
  root->count = 1 + getCount(root->l) + getCount(root->r);
}

void applyDelta(treap *root, int delta) { //lazy update
  if (!root) return;
  root->delta = joinDeltas(root->delta, delta);
  root->nodeValue = joinValueWithDelta(root->nodeValue, delta, 1);
  root->subTreeValue = joinValueWithDelta(root->subTreeValue, delta, root->count);
}

void pushDelta(treap* root) { //lazy update
 if (!root) return;
  applyDelta(root->l, root->delta);
  applyDelta(root->r, root->delta);
  root->delta = NEUTRAL_DELTA;
  
  if (root && root->rev) { //lazy 
		root->rev = false;
		swap (root->l, root->r);
		if (root->l) root->l->rev ^= true;
		if (root->r) root->r->rev ^= true;
	}
}

void merge(treap* &t, treap* l, treap* r) {//assuming l and r are already valid treap??.
  pushDelta(l);
  pushDelta(r);
  if (!l)
    t = r;
  else if (!r)
    t = l;
  else if (l->prio < r->prio)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  update(t); //both left and right child will have subtree sum already updated, so updating cur node.
}


//note: only moving of pointers happening, so that a whole subtree rooted from x from somewhere can be shifted
 // as left subtree of other node by just updating other->l = x;
//Also note: here the order doesnt change,ie:always all nodes rooted at x will be smaller than other.val, and viceversa for right
/*all pos <key(0-based) to left and remaining to right*/
void split(treap* t, treap* &l, treap* &r, int key) {
  pushDelta(t);
  if (!t)
    l = r = NULL;
  else if (key <= getCount(t->l))
    split(t->l, l, t->l, key), r = t;   //all right subtree and cur node belongs to right(r=t), and spliting happens on left subtree
  else
    split(t->r, t->r, r, key - getCount(t->l) - 1), l = t;//all left subtree and curr node belongs to left(l=t),and then spliting happens on right subtree.
  update(t); //
}

int get(treap* t, int index) {
  pushDelta(t);
  if (index < getCount(t->l))
    return get(t->l, index);
  else if (index > getCount(t->l))
    return get(t->r, index - getCount(t->l) - 1);
  return t->nodeValue;
}

//insert such that all elements below item has its prio > item.prio & all left of item has val<item.val & all right has val >item.val.
//so first reach the prio level in crt traversing based on ind, then do split and put all smaller to left & viceversa
void insert(treap* &t, treap* item, int index) {
  pushDelta(t);
  if (!t)
    t = item;
  else if (item->prio < t->prio)
    split(t, item->l, item->r, index), t = item;
  else if (index <= getCount(t->l))
    insert(t->l, item, index);
  else
    insert(t->r, item, index - getCount(t->l) - 1);
  update(t);
}

void insert(treap* &root, int index, int value) {
  treap *item = &nodes[nodes_cnt];
  item->nodeValue = value;
  item->subTreeValue = value;
  item->delta = NEUTRAL_DELTA;
  item->count = 1;
  item->prio = rnd[nodes_cnt];
// it->prio = (rand() << 15) + rand();
  ++nodes_cnt;
  insert(root, item, index);
}

void remove(treap* &t, int index) {
  pushDelta(t);
  if (index == getCount(t->l))
    merge(t, t->l, t->r);
  else
    if (index < getCount(t->l))
      remove(t->l, index);
    else
      remove(t->r, index - getCount(t->l) - 1);
  update(t);
}

//http://e-maxx.ru/algo/treap#4
void reverse (treap* &t, int l, int r) {
	treap *t1, *t2, *t3;
	split(t, t1, t2, l);
	split(t2, t2, t3, r-l+1);
	t2->rev ^= true;
	treap *tt;
	merge(tt, t1, t2);
	merge(t, tt, t3);
}


//for each needed nodes, ans is found by Union(cur->l,cur,cur->right) whenever spliting merge happens.
int query(treap* &root, int a, int b) {
  treap *l1, *r1;
  split(root, l1, r1, b + 1);
  treap *l2, *r2;
  split(l1, l2, r2, a);
  int res = getSubTreeValue(r2);
  treap *t;
  merge(t, l2, r2);
  merge(root, t, r1);
  return res;
}

void modify(treap* &root, int a, int b, int delta) {
  treap *l1, *r1;
  split(root, l1, r1, b + 1);
  treap *l2, *r2;
  split(l1, l2, r2, a);
  applyDelta(r2, delta);
  treap *t;
  merge(t, l2, r2);
  merge(root, t, r1);
}

void print(treap* t) {
  if (!t) return;
  pushDelta(t);
  print(t->l);
  cout << t->nodeValue << " ";
  print(t->r);
}

// Random test
int main() {

	#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    
  for (int i = 0; i < MAXN; i++)
    rnd.push_back(i);
  random_shuffle(rnd.begin(), rnd.end());
  
  treap* t = NULL;

  /*----------------------no need---------------------------*/
  vector<int> list;

  for (int step = 0; step < 3000; step++) {
    int cmd = rand() % 6;
    if (cmd < 2 && list.size() < 100) {
      int pos = rand() % (list.size() + 1);
      int delta = rand() % 100;
      list.insert(list.begin() + pos, delta);
      insert(t, pos, delta);
    } else if (cmd < 3 && list.size() > 0) {
      int pos = rand() % list.size();
      list.erase(list.begin() + pos);
      remove(t, pos);
    } else if (cmd < 4 && list.size() > 0) {
      int b = rand() % list.size();
      int a = rand() % (b + 1);
      int res = list[a];
      for (int i = a + 1; i <= b; i++)
        res = joinValues(res, list[i]);
      int q = query(t, a, b);
      if (res != q) {
        for(int i = 0; i < list.size(); i++) cout << list[i] << endl;
        print(t);
        return 0;
      }
    } else if (cmd < 5 && list.size() > 0) {
      int b = rand() % list.size();
      int a = rand() % (b + 1);
      int delta = rand() % 100;
      for (int i = a; i <= b; i++)
        list[i] = joinValueWithDelta(list[i], delta, 1);
      modify(t, a, b, delta);
    } else {
      for (int i = 0; i < list.size(); i++) {
        int q1 = query(t, i, i);
        int q2 = get(t, i);
        if (list[i] != q1 || q1 != q2) {
          for(int i = 0; i < list.size(); i++) cout << list[i] << endl;
          print(t);
          return 0;
        }
      }
    }
  }
  cout << "Test passed" << endl;
}

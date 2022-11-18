//biparite matching in O(V.E)

vector<vector<int>> g; //contains biparite graph
vector<int> with;
vector<int> usd;
 
int dfs(int v) {
    if (usd[v]) return 0;
    usd[v] = 1;
    for (auto &to : g[v]) {
        if (with[to] == -1) {
            with[to] = v;
            return 1;
        }
    }
    for (auto &to : g[v]) {
        if (dfs(with[to])) {
            with[to] = v;
            return 1;
        }
    }
    return 0;
}

int main(){

  vector<int> l, r; //contains all nodes in left in l, and right in r.
  
   g.resize(l.size());
    with.resize(r.size(), -1);
    for (int i = 0; i < (int)l.size(); i++) {
        for (int j = 0; j < (int)r.size(); j++) {
            if (l[i] % r[j] == 0 && 2 * l[i] + r[j] <= A) { //condn for jth element of right column to be present in ith set. //ie:edge b/w i and j.
                g[i].psuh_back(j);
            }
        }
    }
    
    //biparite matching in O(V.E).
    int cnt = 0;
    for (int i = 0; i < (int)l.size(); i++) {
        usd.assign(l.size(), 0);
        cnt += dfs(i);
    }
    if (cnt < (int)l.size()) { //no soln
        cout << -1;
        return 0;
    }
    
    
     vector<pair<int, int>> ans; //contains matching pairs.
    for (int j = 0; j < (int)r.size(); j++) {
        if (with[j] == -1) {
            continue;
        } else {
            ans.push_back(l[with[j]],r[j]);
        }
    }
    
    cout << ans.size() << "\n";
    for (auto &c : ans) cout << c.first << " " << c.second << "\n";

}

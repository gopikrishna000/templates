
int timer=0 , n;
vector<int> start,endx , brr ,c; 
vector<vector<int>> arr;
 
void dfs(int root,int par){
    // cerr<<root<<"x ";
    start[root] = timer;
    timer++;
    brr.push_back(c[root]);
 
    for(auto &x:arr[root]){
        if(x!=par){
            //   cerr<<x<<"y ";
            dfs(x,root);
        }
    }
 
    endx[root] = timer;
    timer++;
    brr.push_back(c[root]);
}


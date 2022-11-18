/*note: here it find only kth zero/one from first index.
for general range[l,r], just find {x = #1s in [0,l-1]} then find x+1th
one from first index, for ans...similarly for zero. */

//kth one
int find_kth(int v, int tl, int tr, int k) {
   push(v,tl,tr);
    if (k > t[v]){       
        return -1;
    }
    if (tl == tr)
        return tl;  

    int tm = (tl + tr) / 2;
 push(v*2,tl,tm);  

    if (t[v*2] >= k)
        return find_kth(v*2, tl, tm, k);
    else 
        return find_kth(v*2+1, tm+1, tr, k - t[v*2]);
}

//kth zero
int find_k(int v, int tl, int tr, int k) {
    push(v,tl,tr);
    if (k > tr-tl+1-t[v]){       
        return -1;
    }
    
    if (tl == tr)
        return tl;     

    int tm = (tl + tr) / 2;
 push(v*2,tl,tm);  

    if (tm-tl+1 - t[v*2] >= k)
        return find_k(v*2, tl, tm, k);
    else 
        return find_k(v*2+1, tm+1, tr, k - (tm-tl+1 - t[v*2]));
}


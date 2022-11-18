the implicit key for some vertex t is equal to the number of vertices cnt(t->l) in that vertex's left subtree, plus the equivalent values ​​cnt(p->l)+1 for each ancestor p of that vertex, provided that t is in right subtree for p.

note: given curr pos/node, then next pos in implicit tree will be 

insert O(logn)

remove O(logn)

merge O(logn) //It works under the assumption that T 1 and T 2 have the corresponding order (all X values ​​in the first(T1) are less than the X values ​​in the second(T2))

union(T1,T2) & intersect(T1,T2) O (M log (N/M)) //when both T1 and T2 are not in correct order already.
or MlogN - MlogM ;N>M ; ie: logarithmic distance b/w N and M should be huge enough.
eg: O(M) if N=M^2, so on... so O(sqrt(maxm)) possible.

reverse(l,r) 


//ref:https://sites.google.com/site/indy256/algo_cpp/treap

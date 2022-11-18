//lcp[i] = lcp of s[i] and s[i+1] //so lcp[n-1]=0 default.
//0-based index
vector<int> kasai(string s, vector<int> sa)
{
    int n=s.size(),h=0;
    vector<int> lcp(n,0);
    vector<int> rank(n,0);

    for(int i=0; i<n; i++) rank[sa[i]]=i;

    for(int i=0; i<n; i++)
    {
        if(rank[i]==n-1) {h=0; continue;}
        int j=sa[rank[i]+1];
        while(i+h<n && j+h<n && s[i+h]==s[j+h]) 
            h=h+1;
        lcp[rank[i]]=h;
        if(h>0)
            h=h-1;
    }
    return lcp;
}

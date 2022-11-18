#include <bits/stdc++.h>
using namespace std;

// note: node number in yt and this implementation is exactly same
#define fpos adla // fpos is ambigious
const int Inf = 1e9 + 9;
const int Maxn = 1e6; // maxm # of nodes possible
int s[Maxn];          // will become original string or array.
map<int, int> to[Maxn];
/*to[i] where i is node id, to[i].first is ascii value(or array value) of first element in
branch/segment. to[i].second is id(for map,fpos,len) of that key/node,
using which len[to[i].second] gives length of branch/segment.
since map used, so we get in sorted order.
to[0] is root node.
*/

int len[Maxn], fpos[Maxn], link[Maxn];
/*fpos[i](0-based), if substring['a':'b'] is edge present with node i(ie:id=i), then fpos[i] is
pos of 'a' in inputstring such that root->'a':'b'->(longest path)    	//link is for only building
                                           |
                                        fpos[i]    eg: fpos[to[0]['c']] = 0, ie:catcgcat$
eg2: fpos[to[4]['a']] = 1
-----------------------
or in other words, fpos[i] is starting pos of edge['a':eof] when first created,
or when first created a branch['b':eof] from['a':eof].
-----------------------
use:it will be helpful to traverse substring/subarray contained in a node:[arr[fpos[i]],arr[fpos[i]+len[i]-1]
*/

int node, pos;
int sz = 1, nn = 0; // sz is numbers of nodes so far., nn will become size of input array

int make_node(int _pos, int _len)
{
    fpos[sz] = _pos;
    len[sz] = _len;
    return sz++;
}

void go_edge() // suffix link jump
{
    while (pos > len[to[node][s[nn - pos]]])
    {
        node = to[node][s[nn - pos]];
        pos -= len[node];
    }
}

void add_letter(int c)
{
    s[nn++] = c;
    pos++;
    int last = 0;
    while (pos > 0)
    {
        go_edge();
        int edge = s[nn - pos];
        int &v = to[node][edge];
        int t = s[fpos[v] + pos - 1];
        if (v == 0)
        {
            v = make_node(nn - pos, Inf);
            link[last] = node;
            last = 0;
        }
        else if (t == c)
        {
            link[last] = node;
            return;
        }
        else
        {
            int u = make_node(fpos[v], pos - 1);
            to[u][c] = make_node(nn - 1, Inf);
            to[u][t] = v;
            fpos[v] += pos - 1;
            len[v] -= pos - 1;
            v = u;
            link[last] = u;
            last = u;
        }
        if (node == 0)
            pos--;
        else
            node = link[node];
    }
}

int dfs1(int root, vector<int> &cnt, vector<int> &start, int k)
{
    if (to[root].size() == 0)
    {

        cnt[root] = 1;
        start[root] = fpos[root] - k;
    }

    for (auto &x : to[root])
    {
        start[root] = fpos[root] - k;
        cnt[root] += dfs1(x.second, cnt, start, k + len[root]);
    }
    return cnt[root];
}

int main()
{
    /*-----------------------------------needed----------------------------------*/

    string ss = "catcgcat$"; // catcgcat also works fine.  /*hwv.dk/st.html*/

    int n = ss.size();
    // scanf("%d", &n);
    // std::vector<int> arr(n + 1);   //for array
    // for (int i = 0; i < n; i++)
    //     scanf("%d", &arr[i]);
    // arr[n] = -1 * Inf;           //eof is essential, if we need to count # of repetitions
    // n++;

    for (int i = 0; i < 4 * n; i++) // clearing all
    {
        to[i].clear();
        s[i] = 0, len[i] = 0, fpos[i] = 0, link[i] = 0;
    }

    sz = 1, nn = 0;
    len[0] = Inf;
    for (int i = 0; i < ss.size(); i++)
        add_letter(ss[i]);
    /*0 is root node that doesnt have any length/edge., each edge before a node belongs to node.*/
    for (int i = 1; i < sz; i++)
        len[i] = min((int)ss.size() - fpos[i], len[i]);
    /*------------------------------------needed----------------------------------*/

    /*-----------------------optional----------------------*/
    vector<int> cnt(sz), start(sz); // cnt[i] stores # of different endings for node i.
    dfs1(0, cnt, start, 0);         // start[i] stores very starting index of node i, ie:from root.
    // so that start[i] to fpos[i]-1 is parent path for node i,and fpos[i] to fpos[i]+len[i]-1 is range of node i.
    /*-----------------------optional----------------------*/

    /*---------------extra-------------------*/
    // printing tree
    cerr << "id:fst-chr-id2 id2 substr-id2\n";
    for (int i = 0; i < sz; i++)
    {

        for (auto &x : to[i])
        {
            cerr << i << ": " << char(x.first) << " " << x.second << " ";
            for (int i = fpos[x.second]; i < fpos[x.second] + len[x.second]; i++)
                cerr << ss[i];
            cerr << "\n";
        }

        if (to[i].size())
            cerr << "\n";
    }
    /*---------------extra--------------------*/
}

// hwv.dk/st.html  //online construction visual
//https://photos.app.goo.gl./oTGxNPreQ7S6QpLA7

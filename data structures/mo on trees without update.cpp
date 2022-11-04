#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define SD ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
#define pb emplace_back
// problem link https://www.spoj.com/problems/COT2/
const int N = 1e6+7;
int n,q,a[N],qs[N],qe[N],qi[N],qLCA[N],freq[N],qAns[N],s,e,dep[N],sq,ans;
int stTime[N],enTime[N],curTime,time2index[N];
int index2node[N],dfn,node2index[N];
vector<vector<int>> gr;
void dfs(int src,int par) {
    index2node[dfn] = src;
    node2index[src] = dfn++;
    stTime[src] = curTime++;
    time2index[curTime-1] = src;
    dep[src] = dep[par]+1;
    for(auto it:gr[src]) {
        if(it == par) continue;
        dfs(it,src);
        index2node[dfn++] = src;
    }
    enTime[src] = curTime++;
    time2index[curTime-1] = src;
}
int sp[20][N] , lg[N];
void buildSP() {
    lg[0] = -1;
    for(int i = 0 ; i < dfn ; i++) {
        lg[i+1] = lg[i] + !(i&(i+1));
        sp[0][i] = i;
    }
    for(int j = 1 ; (1<<j) <= dfn ; j++) {
        for(int i = 0 ; i + (1<<j) <= dfn ; i++) {
            int a = sp[j-1][i] , b = sp[j-1][i+(1<<(j-1))];
            sp[j][i] = dep[index2node[a]] < dep[index2node[b]]?a:b;
        }
    }
}
int LCA(int u,int v) {
    if(u==v) return u;
    u = node2index[u];
    v = node2index[v];
    if(v>u)swap(u,v);
    int len = lg[u-v];
    int a = sp[len][v] , b = sp[len][u-(1<<len)+1];
    a = index2node[a] , b = index2node[b];
    if(dep[a] < dep[b]) return a;
    return b;
}
bool isOdd[N];
void add(int val) {
    ans += !freq[val]++;
}
void del(int val) {
    ans -= !--freq[val];
}
void flip(int val) {
    if(isOdd[val] ^= 1) add(a[val]);
    else del(a[val]);
}
void updateSE(int idx) {
    while(e < qe[idx] + 1) flip(time2index[e++]);
    while(s > qs[idx]) flip(time2index[--s]);
    while(s < qs[idx]) flip(time2index[s++]);
    while(e > qe[idx] + 1) flip(time2index[--e]);
}

int32_t main(){
    SD;
    cin >> n >> q;
    gr.resize(n+2);
    dep[0]=-1;
    vector<int> com;
    for(int i = 0 ; i < n ; i++) {
        cin >> a[i+1];
        com.pb(i+1);
    }
    sort(com.begin(),com.end() , [](int x,int y) {return a[x] < a[y];});
    for(int i = 0 ,cot=1; i < n ; cot++) {
        int j = i;
        while(j<n && a[com[j]] == a[com[i]])j++;
        while(i < j) a[com[i++]] = cot;
    }
    for(int i = 0 ; i < n-1 ; i++) {
        int x,y;
        cin>>x>>y;
        gr[x].pb(y);
        gr[y].pb(x);
    }
    dfs(1,0);
    buildSP();
    sq = sqrt(curTime);
    for(int i = 0 ; i < q ; i++) {
        int u,v;
        cin>>u>>v;
        if(stTime[u] > stTime[v]) swap(u,v);
        int lca = LCA(u,v);
        qi[i] = i;
        qLCA[i] = lca;
        if(u == lca) {
            qs[i] = stTime[u] + (u==lca);
            qe[i] = stTime[v];
        }else {
            qs[i] = enTime[u];
            qe[i] = stTime[v];
        }
    }
    sort(qi,qi+q,[](int x,int y){return make_pair(qs[x]/sq,qe[x]) < make_pair(qs[y]/sq,qe[y]);});
    for(int i = 0 ; i < q ; i++) {
        updateSE(qi[i]);
        add(a[qLCA[qi[i]]]);
        qAns[qi[i]] = ans;
        del(a[qLCA[qi[i]]]);
    }
    for(int i = 0 ; i < q; i++) {
        cout << qAns[i] << "\n";
    }
    return 0;
}

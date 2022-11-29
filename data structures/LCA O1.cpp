vector<vector<int>> gr;
int n;
int stN[N], depth[N], tim, eu[2*N], lg[2*N], sp[20][2*N];
void dfs(int src,int pr) {
    stN[src] = tim;
    eu[tim++] = src;

    for(auto it:gr[src]) {
        if(it == pr) continue;
        depth[it] = depth[src] + 1;
        dfs(it,src);
        eu[tim++] = src;
    }
}
void sparseTable() {
    lg[0] = -1;
    for(int i = 0 ; i < tim-1 ; i++) {
        sp[0][i] = eu[i];
        lg[i+1] = lg[i] + !(i & (i+1));
    }sp[0][tim-1] = eu[tim-1];

    for(int j = 1 ; (1 << j) <= tim ; j++) {
        for(int i = 0 ; i + (1<<j)-1 < tim ; i++) {
            int c1 = sp[j-1][i];
            int c2 = sp[j-1][i + (1<<(j-1))];
            sp[j][i] = depth[c1]<depth[c2]?c1:c2;
        }
    }
}
void init() {
    memset(depth , 0 , (n+1) * sizeof depth[0]);
    tim = 0;
    dfs(1,0);
    sparseTable();
}
int get_lca(int st,int en) {
    if(en < st) swap(st,en);
    int sz = en-st+1;
    int l = lg[sz];
    int a = sp[l][st];
    int b = sp[l][en - (1<<l)+1];
    return depth[a]<depth[b]?a:b;
}
int lca(int u,int v) {
    return get_lca(stN[u], stN[v]);
}

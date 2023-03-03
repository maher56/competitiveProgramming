struct Hash_tree {
    int p1,p2,m1,m2,pw1[N],pw2[N],sz[N];
    pii h[N];
    void init(int _p1,int _p2,int _m1,int _m2,int n) {
        p1 = _p2;
        p2 = _p2;
        m1 = _m1;
        m2 = _m2;
        pw1[0] = pw2[0] = 1;
        for(int i = 1 ; i < n ; i++) {
            pw1[i] = (1ll*pw1[i-1]*p1)%m1;
            pw2[i] = (1ll*pw2[i-1]*p2)%m2;
        }
        dfs(1,0);
    }
    void dfs(int src,int par) {
        sz[src] = 1;
        vector<pii> h1,h2;
        for(auto it:gr[src]) {
            if(it == par) continue;
            dfs(it,src);
            sz[src] += sz[it];
            h1.push_back({h[it].first,sz[it]});
            h2.push_back({h[it].second,sz[it]});
        }
        sort(h1.begin(),h1.end());
        sort(h2.begin(),h2.end());
        int res1,res2;
        res1 = 2;
        res2 = 3;
        for(auto it:h1) {
            res1 = (1ll * res1 * pw1[it.second] + it.first)%m1;
        }
        for(auto it:h2) {
            res2 = (1ll * res2 * pw2[it.second] + it.first)%m2;
        }
        res1 = (1ll * res1 * p1 + 5)%m1;
        res2 = (1ll * res2 * p2 + 7)%m2;
        h[src] = mp(res1,res2);
    }
} ha;

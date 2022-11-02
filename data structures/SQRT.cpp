int n,a[N];
struct SQRT {
    int SQ = ceil(sqrt(N)) , sq;
    vector<int> pre;
    void init(int n) {
        sq = ceil(sqrt(n));
        pre.resize(SQ);
        int curB = -1;
        for(int i = 0 ; i < sq ; i++) {
            pre[i] = INT_MAX;
        }
        for(int i = 0 ; i < n ; i++) {
            curB += i%sq==0;
            pre[curB] = min(pre[curB] , a[i]);
        }
    }
    int query(int l,int r) {
        int lb = l / sq , rb = r / sq;
        if(lb == rb) return *min_element(a + l , a + r + 1);
        int ret = min(*min_element(a + l , a + (lb+1) * sq) , *min_element(a + rb * sq , a + r + 1));
        if(lb + 1 != rb) ret = min(ret , *min_element(pre.begin() + lb + 1 , pre.begin() + rb));
        return ret;
    }
    void update(int pos,int val) {
        int b = pos / sq;
        a[pos] = val;
        pre[b] = *min_element(a + b * sq , a + (b+1) * sq);
    }
};

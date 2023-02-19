struct Per_SgTree {
    int lf[40*N],rt[40*N],val[40*N],root[N],node_num,lst;
    void init() {
        set_node(root[0] = 1);
        lst = 0;
        node_num = 1;
    }
    void set_node(int node) {
        lf[node] = rt[node] =
        val[node] = 0;
    }
    void insert(int x) {
        set_node(root[++lst] = ++node_num);
        insert(node_num,root[lst-1],x);
    }
    void insert(int cur,int prv,int x,int st=0,int en=n) {
        if(st == en) {
            val[cur] = (prv?val[prv]:0)+1;
            R;
        }
        int mid = st+(en-st)/2;
        if(x <= mid) {
            set_node(lf[cur] = ++node_num);
            rt[cur] = rt[prv];
            insert(lf[cur],lf[prv],x,st,mid);
        }else {
            set_node(rt[cur] = ++node_num);
            lf[cur] = lf[prv];
            insert(rt[cur],rt[prv],x,mid+1,en);
        }
        val[cur] = (lf[cur]?val[lf[cur]]:0)+(rt[cur]?val[rt[cur]]:0);
    }
    int query(int l,int r) {
        R query(root[r],root[l-1],l-1);
    }
    int query(int cur,int prv,int x,int st=0,int en=n) {
        if(!cur) R 0;
        if(st > x) R 0;
        if(en <= x) R val[cur]-(prv?val[prv]:0);
        int mid=st+(en-st)/2;
        R query(lf[cur],lf[prv],x,st,mid)+query(rt[cur],rt[prv],x,mid+1,en);
    }
} sg;

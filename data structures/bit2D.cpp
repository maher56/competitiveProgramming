struct bit2D {
    ll tree[N][N];
    void init() {
        memset(tree , 0 , sizeof tree);
    }
    ll get(int i, int j) {
        ll ret = 0;
        for(++i ; i ; i -= (i&(-i))) {
            for(int jj = j+1 ; jj ; jj -= (jj&(-jj))) {
                ret += tree[i-1][jj-1];
            }
        }
        return ret;
    }
    void add(int i,int j,ll val) {
        for(++i ; i <= N ; i += (i&(-i))) {
            for(int jj = j+1 ; jj <= N; jj += (jj&(-jj))) {
                tree[i-1][jj-1] += val;
            }
        }
    }
    ll get(int si,int sj,int ei,int ej) {
        return get(ei,ej) - get(ei,sj-1) - get(si-1,ej) + get(si-1,ei-1);
    }

} bit;

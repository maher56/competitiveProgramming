struct ST {
    int mat[20][N],lg[N];
    void init() {
        lg[0]=-1;
        for(int i = 1 ; i <= n ;i++) {
            lg[i] = lg[i-1] + !(i&(i-1));
        }
        for(int i = 0 ; i < n ; i++) mat[0][i] = i;
        for(int i = 1 ; (1<<i) <= n ; i++) {
            for(int j = 0 ; j + (1<<i) <= n ; j++) {
                int fi = mat[i-1][j];
                int se = mat[i-1][j+(1<<(i-1))];
                mat[i][j] = a[fi]<a[se]?fi:se;
            }
        }
    }
    int query(int l,int r) {
        if(l > r) R INF;
        int sz = lg[r-l+1];
        int fi = mat[sz][l];
        int se = mat[sz][r-(1<<sz)+1];
        R min(a[fi],a[se]);
    }
} st;

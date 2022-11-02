struct sparseTable {
    int mat[N][int(log2(N))+1],p2[N],m;
    void init(int n) {
        m = int(log2(n))+1;
        p2[0] = p2[1] = 0;
        for(int i = 2 ; i <= n ; i++) {
            p2[i] = p2[i/2]+1;
        }
        for(int i = 0 ; i < n ; i++) {
            mat[i][0] = a[i];
        }
        for(int j = 1 ; j < m ; j++) {
            for(int i = 0 ; i < n ; i++) {
                mat[i][j] = min(mat[i][j-1],mat[i+(1<<(j-1))][j-1]);
//                mat[i][j] = mat[i][j-1] + mat[i+(1<<(j-1))][j-1]; // for sum query
            }
        }
    }
    int query(int l,int r) {
        int pw = p2[r-l];
        return  min(mat[l][pw],mat[r-(1<<pw)+1][pw]);
//        int sum = 0; // for sum query
//        while(l<=r) {
//            sum += mat[l][pw];
//            l += (1<<pw);
//            pw = p2[r-l];
//        }
//        return sum;
    }
} st;

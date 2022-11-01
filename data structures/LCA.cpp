struct LCA {
public:
    int mat[N][(int)log2(N)+5],dep[N],m;
    void init(int n) {
        m = (int)log2(n) + 3;
        calc_sparse(1,0);
    }
    void calc_sparse(int src , int par) {
        mat[src][0] = par;
        for(int i = 1 ; i < m ; i++) { // m = (int)log2(n)+1;
            mat[src][i] = mat[mat[src][i-1]][i-1];
        }
        for(auto it:gr[src]) {
            if(it != par) {
                dep[it] = dep[src] + 1;
                calc_sparse(it,src);
            }
        }
    }
    int get_lca(int x , int y) {
        if(x == y)return y;
        if(dep[x] > dep[y])swap(x,y);
        int dif = dep[y]-dep[x];
        for(int i = m - 1 ; i >= 0 ; i--) {
            if((dif >> i) & 1) {
                y = mat[y][i];
            }
        }
        if(y == x)return y;
        for(int i = m - 1 ; i >= 0 ; i--) {
            if(mat[y][i] != mat[x][i]) {
                y = mat[y][i];
                x = mat[x][i];
            }
        }
        return mat[y][0];
    }
} lca;

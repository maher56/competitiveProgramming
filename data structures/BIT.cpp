struct BIT {
    int tree[N];
    void init() {
        memset(tree , 0 , sizeof(tree));
    }
    void add(int pos,int val) {
        pos++; // if 0-indexed
        while(pos <= N) {
            tree[pos] += val;
            pos += pos & (-pos);
        }
    }
    int get(int pos) {
        pos++; // if 0-indexed
        int ret = 0;
        while(pos) {
            ret += tree[pos];
            pos -= pos & (-pos);
        }
        return ret;
    }
    int get_range(int l,int r) {
        if(l > r) return 0;
        int sum = get(r);
        if(l) sum -= get(l-1);
        return sum;
    }
    // thing like a lower_bound of a prefix sum array
    int find(int t) { // N should be of form 2^x (2 power x)
        int st = 0;
        for(int sz = N >> 1 ; sz ; sz >>= 1) {
            if(tree[st+sz] < t) {
                t -= tree[(st += sz)];
            }
        }
        return st;
    }
} bit;

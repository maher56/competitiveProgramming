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
struct multiSet {
    BIT bit;
    multiSet() {
        bit.init();
        bit.add(0,-1);
    }
    void insert(int val) {
        bit.add(val,1);
    }
    void erase(int val) {
        bit.add(val,-1);
    }
    int count(int val) {
        return bit.get(val) - bit.get(val - 1);
    }
    int size() {
        return bit.get(N - 1) + 1;
    }
    int at(int ind) {
        return bit.find(ind);
    }
    int Lower_Bound(int val ){
        int lo = 0 , hi = size()-1 , mid , idx = 1e9 ;
        while ( lo <= hi ){
            mid = lo+hi >> 1 ;
            if ( at(mid) < val ){
                idx = mid ;
                lo = mid+1 ;
            }
            else
                hi = mid-1 ;
        }
        return idx==1e9?-1:idx ;
    }
} ms;

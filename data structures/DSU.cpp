struct DSU {
public:
    int par[N],sz[N],sets[N],tail[N],nxt[N],pos[N],cot;
    void init(int n) {
        iota(par,par+n,0);
        fill(sz,sz+n,1);
        memset(nxt,-1,n * sizeof(nxt[0]));
        iota(tail,tail+n,0);
        iota(sets,sets+n,0);
        iota(pos,pos+n,0);
        cot = n;
    }
    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }
    bool merge(int u,int v) {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(sz[u] < sz[v]) swap(u,v);
        par[v] = u;
        sz[u] += sz[v];
        int p = pos[v];
        pos[sets[p] = sets[--cot]] = p;
        int &t = tail[u];
        nxt[t] = v;
        t = tail[v];
        return true;
    }
    string toString() {
        stringstream ss;
        ss << '[';
        for(int i = 0 ; i < cot ; i++) {
             ss << "{";
             for(int u = sets[i] ; ~u ; u = nxt[u]) {
                 ss << u;
                 if(~nxt[u]) ss << ',';
             }
             ss << "}";
             if(i < cot-1) ss << ",";

        }
        ss << ']';
        return ss.str();
    }
} dsu;

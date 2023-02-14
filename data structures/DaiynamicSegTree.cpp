struct dai_sg {
    ll val[30*N]lazy[30*N];
    int lf[30*N],rt[30*N],node_num;
    void init() {
        node_num = 1;
        set_node(1);
    }
    set_node(int node) {
        lf[node] = rt[node] = 0;
        val[node] = 0;
        lazy[node] = 0;
    }
    void laz(int st,int en,int node) {
        if(lazy[node]==0) return;
        val[node] += lazy[node]*(en-st+1);
        if(st != en) {
            if(!lf[node]) {
                set_node(lf[node] = ++node_num);
            }
            if(!rt[node]) {
                set_node(rt[node] = ++node_num);
            }
            lazy[lf[node]] += lazy[node];
            lazy[rt[node]] += lazy[node];
        }
        lazy[node] = 0;
    }
    void update(int qs,int qe,int vali,int node=1,int st=1,int en=1e9) {
        laz(st,en,node);
        if(st > qe || en < qs) R ;
        if(st >= qs && en <= qe) {
            lazy[node]+=vali;
            laz(st,en,node);
            return;
        }
        int mid=st+(en-st)/2;
        if(st > qe || mid < qs);
        else {
            if(!lf[node]) {
                set_node(lf[node] = ++node_num);
            }
            val[node] -= val[lf[node]]+lazy[lf[node]]*(mid-st+1);
            update(qs,qe,vali,lf[node],st,mid);
            val[node] += val[lf[node]];
        }
        if(mid+1 > qe || en < qs);
        else {
            if(!rt[node]) {
                set_node(rt[node] = ++node_num);
            }
            val[node] -= val[rt[node]]+lazy[rt[node]]*(en-mid);
            update(qs,qe,vali,rt[node],mid+1,en);
            val[node] += val[rt[node]];
        }
    }
    ll query(int qs,int qe,int node=1,int st=1,int en=1e9) {
        if(!node) R 0;
        laz(st,en,node);
        if(st > qe || en < qs) return 0;
        if(st >= qs && en <= qe) {
            return val[node];
        }
        int mid=st+(en-st)/2;
        return query(qs,qe,lf[node],st,mid)+query(qs,qe,rt[node],mid+1,en);
    }
    // first number greater than zero in range qs qe
    int get_l(int qs,int qe,int node=1,int st=1,int en=1e9) {
        if(!node) R -1;
        laz(st,en,node);
        if(!val[node]) R -1;
        if(st > qe || en < qs) R -1;
        if(st == en) R val[node]?st:-1;
        if(st >= qs && en <= qe) {
            int mid = st+(en-st)/2;
            int z = get_l(qs,qe,lf[node],st,mid);
            if(z == -1) z = get_l(qs,qe,rt[node],mid+1,en);
            R z;
        }
        int mid = st+(en-st)/2;
        int lft,rit;
        if(st > qe || mid < qs) lft=-1;
        else {
            lft = get_l(qs,qe,lf[node],st,mid);
        }
        if(mid+1 > qe || en < qs) rit = -1;
        else {
            rit = get_l(qs,qe,rt[node],mid+1,en);
        }
        R lft==-1?rit:lft;
    }
     // last number greater than zero in range qs qe
    int get_r(int qs,int qe,int node=1,int st=1,int en=1e9) {
        if(!node) R -1;
        laz(st,en,node);
        if(!val[node]) R -1;
        if(st > qe || en < qs) R -1;
        if(st == en) R val[node]?st:-1;
        if(st >= qs && en <= qe) {
            int mid = st+(en-st)/2;
            int z = get_r(qs,qe,rt[node],mid+1,en);
            if(z == -1) z = get_r(qs,qe,lf[node],st,mid);
            R z;
        }
        int mid = st+(en-st)/2;
        int lft,rit;
        if(st > qe || mid < qs) lft=-1;
        else {
            lft = get_r(qs,qe,lf[node],st,mid);
        }
        if(mid+1 > qe || en < qs) rit = -1;
        else {
            rit = get_r(qs,qe,rt[node],mid+1,en);
        }
        R rit==-1?lft:rit;
    }
}sg;

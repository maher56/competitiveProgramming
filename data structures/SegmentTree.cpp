struct ST {
    ll tree[N << 1],lazy[N << 1];
    void build(int st=0,int en=n-1,int idx=0) {
        lazy[idx]=0;
        if(st==en) {
            tree[idx] = a[st];
        }else {
            int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
            build(st,mid,lf);
            build(mid+1,en,rt);
            tree[idx] = tree[lf]+tree[rt];
        }
    }
    void laz(int st,int en,int idx) {
        if(lazy[idx]==0) return;
        tree[idx] += lazy[idx]*(en-st+1);
        if(st != en) {
            int lf=2*idx+1,rt=2*idx+2;
            lazy[lf] += lazy[idx];
            lazy[rt] += lazy[idx];
        }
        lazy[idx]=0;
    }
    void update(int qs,int qe,int val,int st=0,int en=n-1,int idx=0) {
        laz(st,en,idx);
        if(st > qe || en < qs) R ;
        if(st >= qs && en <= qe) {
            lazy[idx] += val;
            laz(st,en,idx);
            return;
        }
        int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
        update(qs,qe,val,st,mid,lf);
        update(qs,qe,val,mid+1,en,rt);
        tree[idx] = tree[lf] + tree[rt];
    }
    ll query(int qs,int qe,int st=0,int en=n-1,int idx=0) {
        laz(st,en,idx);
        if(st > qe || en < qs) return 0;
        if(st >= qs && en <= qe) {
            return tree[idx];
        }
        int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
        return query(qs,qe,st,mid,lf)+query(qs,qe,mid+1,en,rt);
    }
}sg;

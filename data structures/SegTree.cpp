struct ST {
    struct node {
        ll sum,laz;
        node() {
            sum = 0;
            laz= 0;
        }
    } tree[1<<19];
    node merge(node lf,node rt) {
        node ret;
        ret.sum = lf.sum+rt.sum;
        ret.laz = 0;
        return ret;
    }
    void build(int st=0,int en=n-1,int idx=0) {
        if(st==en) {
            tree[idx].sum = a[st];
        }else {
            int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
            build(st,mid,lf);
            build(mid+1,en,rt);
            tree[idx] = merge(tree[lf],tree[rt]);
        }
    }
    void laz(int st,int en,int idx) {
        if(tree[idx].laz==0) return;
        tree[idx].sum += tree[idx].laz*(en-st+1);
        if(st != en) {
            int lf=2*idx+1,rt=2*idx+2;
            tree[lf].laz += tree[idx].laz;
            tree[rt].laz += tree[idx].laz;
        }
        tree[idx].laz=0;
    }
    void update(int qs,int qe,int val,int st=0,int en=n-1,int idx=0) {
        laz(st,en,idx);
        if(st > qe || en < qs) return ;
        if(st >= qs && en <= qe) {
            tree[idx].laz += val;
            laz(st,en,idx);
            return;
        }
        int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
        update(qs,qe,val,st,mid,lf);
        update(qs,qe,val,mid+1,en,rt);
        tree[idx] = merge(tree[lf],tree[rt]);
    }
    ll query(int qs,int qe,int st=0,int en=n-1,int idx=0) {
        laz(st,en,idx);
        if(st > qe || en < qs) return 0;
        if(st >= qs && en <= qe) {
            return tree[idx].sum;
        }
        int mid=st+(en-st)/2, lf=2*idx+1,rt=2*idx+2;
        return query(qs,qe,st,mid,lf)+query(qs,qe,mid+1,en,rt);
    }
}sg;

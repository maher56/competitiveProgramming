struct Node {
    int sz, label;
    Node *p, *pp, *l, *r;
    Node() { p = pp = l = r = nullptr;}
};
typedef Node *node;
void update(node x) {
    x->sz = 1;
    if(x->l) x->sz += x->l->sz;
    if(x->r) x->sz += x->r->sz;
}
void rightRotate(node x) {
    node y, z;
    y = x->p, z = y->p;
    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = nullptr;
    update(y);
}

void leftRotate(node x) {
    node y, z;
    y = x->p, z = y->p;
    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
    x->pp = y->pp;
    y->pp = nullptr;
    update(y);
}

void splay(node x) {
    node y, z;
    while(x->p) {
        y = x->p;
        if(y->p == 0) {
            if(x == y->l) rightRotate(x);
            else leftRotate(x);
        }else {
            z = y->p;
            if(y == z->l) {
                if(x == y->l) rightRotate(y), rightRotate(x);
                else leftRotate(x), rightRotate(x);
            }else {
                if(x == y->r) leftRotate(y), leftRotate(x);
                else rightRotate(x), leftRotate(x);
            }
        }
    }
    update(x);
}

node access(node x) {
    splay(x);
    if(x->r) {
        x->r->pp = x;
        x->r->p = nullptr;
        x->r = nullptr;
        update(x);
    }

    node last = x;
    while(x->pp) {
        node y = x->pp;
        last = y;
        splay(y);
        if(y->r) {
            y->r->pp = y;
            y->r->p = nullptr;
        }
        y->r = x;
        x->p = y;
        x->pp = nullptr;
        update(y);
        splay(x);
    }
    return last;
}

node root(node x) {
    access(x);
    while(x->l) x = x->l;
    splay(x);
    return x;
}

void cut(node x) {
    access(x);
    x->l->p = 0;
    x->l = 0;
    update(x);
}

void link(node x,node y) {
    access(x);
    access(y);
    x->l = y;
    y->p = x;
    update(x);
}

node lca(node x,node y) {
    access(x);
    return access(y);
}

int depth(node x) {
    access(x);
    return x->sz - 1;
}

class LinkCut {
    node x;

    public:
    LinkCut(int n) {
        x = new Node[n];
        for(int i = 0; i < n; i++) {
            x[i].label = i;
            update(&x[i]);
        }
    }

    void link(int u, int v){::link(&x[u], &x[v]);}
    void cut(int u){::cut(&x[u]);}
    int root(int u){return ::root(&x[u])->label;}
    int depth(int u){return ::depth(&x[u]);}
    int lca(int u, int v){return ::lca(&x[u], &x[v])->label;}
};

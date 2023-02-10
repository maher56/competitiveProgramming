// add , delete , get maximum xor with a number
struct Trie {
    struct Node {
        Node*l,*r;
        int freq;
        Node() {
            l = NULL;
            r = NULL;
            freq=0;
        }
    }*root;
    Trie() {
        root = new Node();
    }
    void insert(int x) {
        Node *cur = root;
        for(int i = 31 ; i >= 0 ; i--) {
            if(x & 1 << i) {
                if(cur->r == NULL) cur->r = new Node();
                cur = cur->r;
                cur->freq++;
            }else {
                if(cur->l == NULL) cur->l = new Node();
                cur = cur->l;
                cur->freq++;
            }
        }
    }
    void del(int x) {
        Node *cur = root;
        for(int i = 31 ; i >= 0 ; i--) {
            if(x & 1 << i) {
                cur = cur->r;
                cur->freq--;
            }else {
                cur = cur->l;
                cur->freq--;
            }
        }
    }
    int query(int x) {
        int ans=0;
        Node *cur = root;
        repr(i,31,0) {
            if(x & 1 << i) {
                if(cur->l!=NULL&&cur->l->freq>0) {
                    cur =cur->l;
                    ans |= 1<<i;
                }else {
                    cur =cur->r;
                }
            }else {
                if(cur->r!=NULL&&cur->r->freq>0) {
                    cur =cur->r;
                    ans |= 1<<i;
                }else {
                    cur =cur->l;
                }
            }
        }
        return ans;
    }
} tr;

struct Hash {
    int n,p1,p2,m1,m2,h1[N],h2[N],h3[N],h4[N],pw1[N],pw2[N];
    string s;
    void init(string &str,int _p1,int _p2,int _m1,int _m2) {
        p1 = _p1;
        p2 = _p2;
        m1 = _m1;
        m2 = _m2;
        s = str;
        n = s.size();
        pw1[0] = pw2[0] = 1;
        h1[0] = h2[0] = dif(s[0]);
        for(int i = 1 ; i < n ; i++) {
            h1[i] = (1ll * h1[i-1] * p1 + dif(s[i]))%m1;
            h2[i] = (1ll * h2[i-1] * p2 + dif(s[i]))%m2;
            pw1[i] = (1ll * pw1[i-1] * p1)%m1;
            pw2[i] = (1ll * pw2[i-1] * p2)%m2;
        }
        h3[n-1] = h4[n-1] = dif(s[n-1]);
        for(int i = n-2 ; i >= 0 ; i--) {
            h3[i] = (1ll * h3[i+1] * p1 + dif(s[i]))%m1;
            h4[i] = (1ll * h4[i+1] * p2 + dif(s[i]))%m2;
        }
    }
    int dif(char x) {
        return x-'a'+1;
    }
    pair<int,int> pre_sub(int l,int r) {
        int t1 = h1[r] , t2 = h2[r];
        if(l) {
            t1 = (t1 - (1ll * h1[l-1] * pw1[r-l+1])%m1+m1)%m1;
            t2 = (t2 - (1ll * h2[l-1] * pw2[r-l+1])%m2+m2)%m2;
        }
        return {t1,t2};
    }
    pair<int,int> suf_sub(int l,int r) {
        int t1 = h3[l] , t2 = h4[l];
        if(r+1 < n) {
            t1 = (t1 - (1ll * h3[r+1] * pw1[r-l+1])%m1+m1)%m1;
            t2 = (t2 - (1ll * h4[r+1] * pw2[r-l+1])%m2+m2)%m2;
        }
        return {t1,t2};
    }
    bool pal(int l,int r) {
        return pre_sub(l,r) == suf_sub(l,r);
    }
};

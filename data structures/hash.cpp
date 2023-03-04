struct Hash {
    int n,p1,p2,m1,m2,h1[N],h2[N],pw1[N],pw2[N];
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
    }
    int dif(char x) {
        return x-'a'+1;
    }
    pair<int,int> sub(int l,int r) {
        int t1 = h1[r] , t2 = h2[r];
        if(l) {
            t1 = (t1 - (1ll * h1[l-1] * pw1[r-l+1])%m1+m1)%m1;
            t2 = (t2 - (1ll * h2[l-1] * pw2[r-l+1])%m2+m2)%m2;
        }
        return {t1,t2};
    }
    pair<int,int> merge(int l1,int r1,int l2,int r2) {
        pair<int,int> t1,t2;
        t1 = sub(l1,r1);
        t2 = sub(l2,r2);
        t1.first = (1ll * t1.first * pw1[r2-l2+1] + t2.first)%m1;
        t1.second = (1ll * t1.second * pw2[r2-l2+1] + t2.second)%m2;
        return t1;
    }
} h1;

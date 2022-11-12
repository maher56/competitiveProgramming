struct Hash {
    int n,p1,p2,m1,m2;
    pair<int,int> hash;
    string s;
    vector<int> ha1,ha2,pw1,pw2;
    void init(string &str) {
        s = str;
        n = str.size();
        p1=29;p2=31;
        m1=1e9+7;m2=1e9+11;
    }
    int dif(char x) {
        return int(x-'a'+1);
    }
    ll Mul(ll x,ll y,ll mod=mod){R((x%mod)*(y%mod))%mod;}
    ll Add(ll x,ll y,ll mod=mod){R((x%mod)+(y%mod)+2ll*mod)%mod;}
    void preHash() {
        pw1.resize(n);
        pw2.resize(n);
        ha1.resize(n);
        ha2.resize(n);
        pw1[0]=pw2[0]=1;
        ha1[0]=ha2[0]=dif(s[0]);
        for(int i = 1 ; i < n ; i++) {
            pw1[i] = Mul(pw1[i-1],p1,m1);
            pw2[i] = Mul(pw2[i-1],p2,m2);
            ha1[i] = Add(Mul(ha1[i-1],p1,m1),dif(s[i]),m1);
            ha2[i] = Add(Mul(ha2[i-1],p2,m2),dif(s[i]),m2);
        }
    }
    void build_hash() {
        if(!ha1.empty()) {
            hash.first = ha1[n-1];
            hash.second =ha2[n-1];
            return;
        }
        hash.first = hash.second = dif(s[0]);
        for(int i = 1 ; i < n ; i++) {
            hash.first = Add(Mul(hash.first,p1,m1),dif(s[i]),m1);
            hash.second = Add(Mul(hash.second,p2,m2),dif(s[i]),m2);
        }
    }
    pair<int,int> subHash(int l,int r) {
        int h1=ha1[r],h2=ha2[r];
        if(l) {
            h1 = Add(h1 , -1ll * Mul(ha1[l-1],pw1[r-l+1],m1),m1);
            h2 = Add(h2 , -1ll * Mul(ha2[l-1],pw2[r-l+1],m2),m2);
        }
        R {h1,h2};
    }
}h1,h2;

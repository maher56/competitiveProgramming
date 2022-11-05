#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define SD ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
#define pb emplace_back
// problem link https://www.spoj.com/problems/XXXXXXXX/
const int N = 5e4+5 , Q = 1e5+5;
int n , q , a[N] , comp[N+Q] , compsz , qs[Q] , qe[Q] , qi[Q] , qt[Q] , qAns[Q];
int old[Q],nw[Q],upidx[Q],nq,tim,freq[N+Q] , ans,s,e;
void compres() {
    sort(comp,comp+compsz);
    compsz = unique(comp,comp+compsz)-comp;
    for(int i = 0 ; i < n ;i++) {
        a[i] = lower_bound(comp,comp+compsz,a[i])-comp;
    }
    for(int i = 0 ; i <= tim ;i++) {
        old[i] = lower_bound(comp,comp+compsz,old[i])-comp;
        nw[i] = lower_bound(comp,comp+compsz,nw[i])-comp;
    }
}
void add(int val) {
    ans += (!freq[val]++) * comp[val];
}
void rem(int val) {
    ans -= (!--freq[val]) * comp[val];
}
void updateSE(int i) {
    while(e <= qe[i]) add(a[e++]);
    while(e-1 > qe[i]) rem(a[--e]);
    while(s < qs[i]) rem(a[s++]);
    while(s > qs[i]) add(a[--s]);

    while(tim < qt[i]) {
        tim++;
        if(upidx[tim]>= s && upidx[tim]<e) {
            rem(old[tim]);
            add(nw[tim]);
        }
        a[upidx[tim]] = nw[tim];
    }
    while(tim > qt[i]) {
        if(upidx[tim]>= s && upidx[tim]<e) {
            rem(nw[tim]);
            add(old[tim]);
        }
        a[upidx[tim]] = old[tim];
        tim--;
    }
}
int32_t main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    SD;
    cin >> n;
    for(int i = 0 ; i < n ; i++) {
        cin >> a[i];
        comp[i] = a[i];
    }
    cin >> q;
    compsz = n;
    for(int i = 0 ; i < q ; i++) {
        char ch;int x,y;
        cin>>ch>>x>>y;
        if(ch == 'Q') {
            qi[nq] = nq;
            qs[nq] = --x;
            qe[nq] = --y;
            qt[nq] = tim;
            nq++;
        }else {
            tim++;
            upidx[tim] = --x;
            old[tim] = a[x];
            nw[tim] = y;
            a[x] = y;
            comp[compsz++] = y;
        }
    }
    compres();
    int bz = ceil(pow(n,2.0/3.0));
    sort(qi,qi+nq,[&](int x,int y) {
        int bsx = qs[x]/bz , bsy = qs[y]/bz;
        int bex = qe[x]/bz , bey = qe[y]/bz;
        return tie(bsx,bex,qt[x]) < tie(bsy,bey,qt[y]);
    });
    for(int i = 0 ; i < nq ; i++) {
        updateSE(qi[i]);
        qAns[qi[i]] = ans;
    }
    for(int i = 0 ; i < nq ; i++) {
        cout << qAns[i] << " \n"[i==nq-1];
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
// here the solution for problem https://www.spoj.com/problems/DQUERY/
const int N = 1e6;
int freq[N],a[N],qs[N],qe[N],qi[N],qAns[N],n,q,sq,s,e,ans;
void add(int x) {
    ans += !freq[x]++;
}
void del(int x) {
    ans -= !--freq[x];
}
void updateSE(int idx) {
    while(e < qe[idx]+1) add(a[e++]);
    while(s > qs[idx]) add(a[--s]);
    while(s < qs[idx]) del(a[s++]);
    while(e > qe[idx]+1) del(a[--e]);
}
int main() {
    cin >> n;
    for(int i = 0 ; i < n ; i++)
        cin >> a[i];
    cin >> q;
    for(int i = 0 ; i < q ; i++) {
        cin >> qs[i] >> qe[i];
        --qs[i];--qe[i];
        qi[i] = i;
    }
    sq = sqrt(n);
    sort(qi , qi + q , [](int x,int y) {return make_pair(qs[x]/sq,qe[x]) < make_pair(qs[y]/sq,qe[y]);});
    for(int i = 0 ; i < q ; i++) {
        updateSE(qi[i]);
        qAns[qi[i]] = ans;
    }
    for(int i = 0 ; i < q ; i++) {
        cout << qAns[i] << endl;
    }
    return 0;
}

//https://codeforces.com/contest/1096/problem/G

#include <iostream>
#include <bits/stdc++.h>

#define ll long long
using namespace std;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define rep(n) for(int macroIterator = 0; macroIterator < n; macroIterator++)
#define forn(i, n) for(int i = 0; i < n; i++)
#define forn2(i, n) for(int i= 1; i <= n; i++)
#define si(n) scanf("%d", &n)
#define sii(n, m) scanf("%d %d", &n, &m)
#define siii(n, m, l) scanf("%d %d %d", &n, &m, &l)

#define sz(x) (int)x.size()

#define MOD 998244353
#define inf 0x3f3f3f3f

const int len = 1 << 20, g = 3;
int n, k;
ll A[len], R[len];

ll pw(ll a, ll r = -1) {
    ll ret = 1;
    if(r < 0) {
        a = pw(a, MOD - 2);
        r = -r;
    }
    for(; r; r >>= 1, a = a*a%MOD) {
        if(r & 1) ret = ret*a%MOD;
    }
    return ret;
}

void NTT(int typ = 1) {
    forn(i, len) {
        if(i < R[i]) swap(A[i], A[R[i]]);
    }
    for(int l = 2; l <= len; l <<= 1) {
        for(int pos = 0; pos < len; pos += l) {
            ll wn = pw(g, typ*(MOD - 1)/l), w = 1;
            for(int i = pos; i < pos + l/2; i++) {
                ll P = A[i];
                ll M = A[i + l/2]*w % MOD;
                A[i] = (P + M)%MOD;
                A[i + l/2] = (P - M)%MOD;
                w = w*wn % MOD;
            }
        }
    }
    if(typ == -1) {
        ll rv = pw(len, -1);
        //printf("rev: %lld\n", rv);
        forn(i, len) A[i] = A[i]*rv % MOD;
    }
}

int main() {
    sii(n, k);
    n >>= 1;
    forn(i, k) {
        int d; si(d);
        A[d] = 1;
        //A[i] = d;
    }
    forn(i, len) {
        R[i] = R[i>>1]>>1 | (i&1)*(len >> 1);
    }
    NTT();
    forn(i, len) A[i] = pw(A[i], n);
    NTT(-1);
    ll sum = 0;
    forn(i, len) sum = (sum + A[i]*A[i] % MOD)%MOD;
    if(sum < 0) sum += MOD;
    printf("%lld", sum);

}

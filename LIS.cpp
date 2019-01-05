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

#define MOD ((ll)1e9 + 7)
#define inf 0x3f3f3f3f
#define large (int)1e5

int arr[550], ans, n;

void doLIS(int st) {
    vector<int> lastDigit(n+1, inf);
    vector<int> prevPos(n+1), pos(n+1);
    lastDigit[1] = arr[st];
    prevPos[st] = -1;
    pos[1] = st;
    int maxL = 1, maxPos = st;
    ans++;
    for(int i = st + 1; i < n; i++) {
        //forn(i, n+1) printf("%d ", lastDigit[i]);

        auto itr = upper_bound(lastDigit.begin(), lastDigit.end(), arr[i]);
        int toFix = itr - lastDigit.begin();

        //printf("TOFIX: %d\n", toFix);
        if(toFix == 0) {
            lastDigit[1] = arr[i];
            prevPos[i] = -1;
            pos[1] = i;
        }
        else {
            lastDigit[toFix] = arr[i];
            prevPos[i] = pos[toFix-1];
            pos[toFix] = i;
            if(toFix > maxL) {
                maxL = toFix;
                maxPos = i;
            }
        }
        ans += maxL;
    }
    printf("The length of LIS is: %d\n", maxL);
    deque<int> sta;
    for(int last = maxPos; last != -1; last = prevPos[last]) {
        sta.push_front(last);
    }
    for(int k : sta) printf("%d ", arr[k]);
}

void solve(int tc) {
    ans = 0;
    si(n);
    forn(i, n) si(arr[i]);
    forn(i, 1) doLIS(i);
    printf("Case #%d: %d\n", tc+1, ans);
}

int main() {
    int t; si(t);
    forn(i, t) solve(i);
}

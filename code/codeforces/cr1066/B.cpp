#include <bits/stdc++.h>
#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0; ll x, y = 0; cin >> n >> x >> y;
    vector<int> a(n);
    if (x == 0 && y == 0) {
        cout << "YES" << NL;
        return;
    } else {
        for (int i = 0; i < n; ++i) cin >> a[i];
        
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0; cin >> t;
    while (t--) solve();
}
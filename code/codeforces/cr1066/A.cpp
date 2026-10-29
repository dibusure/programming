#include <bits/stdc++.h>
#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0, tmp = 0; cin >> n;
    vector<int> a(n+1, 0);
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        a[tmp]++;
    }

    for (int i = 0; i <= n; ++i) {
        if (a[i] > 0 && a[i] != i) {
            if (a[i] > i) {
                //cout << i << " встречается " << a[i] << " раз, а должно " << i << " => " << a[i]-i << NL;
                ans += a[i] - i;
            } else {
                //cout << i << " встречается " << a[i] << " раз, а должно " << 0 << " => " << a[i]-0 << NL;
                ans += a[i] - 0;
            }
        }
    }

    cout << ans << NL;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0; cin >> t;
    while (t--) solve();
}
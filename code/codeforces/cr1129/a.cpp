#include <bits/stdc++.h>

#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define INF 100000007
#define pb push_back
typedef long long ll;
using namespace std;

void solve() {
    int k = 0, n = 0;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // why do we need k anyway?
    sort(all(a));
    int res = 0;
    int i = 0;
    while (a[i] == i)
        res++;
    cout << res << NL;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0; cin >> t;
    while (t--) solve();
}

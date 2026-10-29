#include <bits/stdc++.h>

#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define INF 100000007
#define pb push_back
typedef long long ll;
using namespace std;

void solve() {
    ll x1 = 0, y1 = 0, r1 = 0, x2 = 0, y2 = 0, r2 = 0;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
    ll l_sq = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
    if (l_sq > (r1+r2)*(r1+r2)) {
        cout << "No" << NL;
    } else {
        if (l_sq < (r1-r2)*(r1-r2)) {
            cout << "No" << NL;
        } else {
            cout << "Yes" << NL;
        }
    }

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0; cin >> t;
    while (t--) solve();
}

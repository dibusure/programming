#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0;
    ll cost = 0, tmp = 0;
    cin >> n;
    vector<ll> a;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;        
        a.push_back(tmp);
    }
    
    sort(a.begin(), a.end());

    for (int i = n-1; i >= 0; i-=2) {
        cost += a[i];
    }

    cout << cost << NL;
    return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    int t = 0;
    cin >> t;
    while (t--) solve();
}

#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    ll n = 0;
    bool res = false;
    cin >> n;
    vector<ll> vec;

    for (int k = 1; pow(10,k) <= n; ++k) {
        if (n % ((ll)pow(10,k) + 1) == 0) {
            #ifdef DEB
            cout << n << " % " << (ll)pow(10,k) + 1 << NL;
            #endif
            vec.push_back(n / (ll)(pow(10,k) + 1));
            res = true;
        }
    }

    if (!res) {
        cout << 0 << NL;
    } else {
        reverse(vec.begin(), vec.end());
        cout << vec.size() << NL;
        for (int i = 0; i < vec.size(); ++i)
            cout << vec[i] << " ";
        cout << NL;
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0;
    cin >> t;
    while (t--) solve();
}

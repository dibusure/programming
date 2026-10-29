#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    ll n = 0, sum = 0;
    cin >> n;
    sum = ((n+1)*n)/2;
    if (sum%2 == 1) {
        cout << "NO" << NL;
    } else {
        sum /= 2;
        ll local_sum = 0, max_el = n-1, counter = 0;
        vector<ll> v(n);
        iota(v.begin(), v.end(), 1);

        for (ll i = n-1; i >= 1; i--) {
            if (sum - local_sum <= v[max_el]) {
                v[sum-local_sum-1] = 0;
                local_sum = 0;

                ++counter;
                break;
            } else {
                local_sum += v[i];
                v[i] = 0;
                --max_el;
                ++counter;
                #ifdef DEB
                cout << "++counter: " << counter << NL;
                #endif
            }
        }

        cout << "YES" << NL;

        cout << n - counter << NL;

        for (ll i = 0; i < n; ++i) {
            if (v[i] != 0)
                cout << v[i] << " ";
        }
        cout << "\n";

        cout << counter << NL;

        for (ll i = 0; i < n; ++i) {
            if (v[i] == 0)
                cout << i+1 << " ";
        }

        cout << "\n";
    }
}

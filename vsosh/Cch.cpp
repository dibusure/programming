#include <bits/stdc++.h>
#define NL "\n"
typedef long long ll;

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    int n = 0;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
     ll total = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        total += a[i];
    }
    sort(a.begin(), a.end());

    ll bestKeep = 0;
    for (int i = 0; i < n; ++i) {
         ll t = a[i];
         ll count = n - i;
         ll keep = t * count;
        if (keep > bestKeep) bestKeep = keep;
    }

    cout << (total - bestKeep) << NL;
    return 0;
}


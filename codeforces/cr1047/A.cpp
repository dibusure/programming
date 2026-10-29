#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int Kollatz(int x, int k) {
    for (int i = 0; i <= k; ++i) {
        if (x%2==1) {
            x*=2;
        } else {
            --x;
            x/=3;
        }
    }
    return x;
}

void solve() {
    int x = 0, k = 0;
    cin >> k >> x;
    if (x%2 == 1) {
        cout << Kollatz(x, k) << NL;
    } else {
        // if x%2 == 0 then it can be reached both ways
        // if x_k-1 % 2 == 0
        while (Kollatz(x, k) <= 0) {
            x*=2;
            --k;
        }
        cout << x << NL;
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 0; cin >> t;
	while (t--) solve();
}


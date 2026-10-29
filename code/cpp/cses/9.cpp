#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    ll n = 0, ans = 1, MOD = pow(10,9) + 7;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ans *= 2;
        if (ans > MOD)
            ans -= MOD;
    }


    cout << ans << NL;
}

#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n = 0;
    cin >> n;
    ll sum = (n*n+n)/2, tmp = 0;

    for (ll i = 0; i < n-1; ++i) {
        cin >> tmp;
        sum -= tmp;
    }

    cout << sum << NL;
}

#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

// TODO: long long int

ll find_number(ll x, ll y) {
    if (x==y) {
        return 1+x*(x-1);
    } else {
        if (x>y) {
            if (x%2==1) {
                return 1 + x*(x-1) + (x-y);
            } else {
                return 1 + x*(x-1) - (x-y);
            }
        } else {
            if (y%2==1) {
                return 1 + y*(y-1) - (y-x);
            } else {
                return 1 + y*(y-1) + (y-x);
            }
        }
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    ll x = 0, y = 0, t = 0;

    cin >> t;

    for (ll i = 0; i < t; ++i) {
        cin >> y >> x;
        cout << find_number(x, y) << NL;
    }
}

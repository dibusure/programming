#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

ll ans(ll k) {
    if (k==1) {
        return 0;
    } else if (k==2) {
        return 6;
    } else {
        ll all_paris = (k*k*(k*k-1))/2;
        ll berlin = (8*(k-1)*(k-2))/2;
        return (ll)(all_paris - berlin) ;
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    int n = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cout << ans((ll)i) << NL;
    }
}

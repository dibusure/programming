#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    ll n = 0, prev = 0, cur = 0, steps = 0;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        if (i==0) {
            cin >> prev;
        } else {
            cin >> cur;
            if (cur < prev) {
                steps += prev-cur;
                cur = prev;
            }
            prev=cur;
        }

    }

    cout << steps << NL;
}

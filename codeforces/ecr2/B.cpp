#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

#define NL "\n";
typedef long long ll;

using namespace std;

bool isBeaut(vector<ll> &v) {
    for (ll i = 1; i < v.size(); ++i) {
        if (abs(v[i-1] - v[i]) <= 1) {
            return true;
        }
    }

    return false;
}

int ans(vector<ll> &v) {
            // if array is sorted => -1
            // else if array is already beautiful => 0
            // else (array is unsorted and not already beautiful) => 1 -- because it has a local extremum

            // if array is unsorted, then we have a part like:
            // let's consider a_{i-1} as a, a_i as b and a_{i+1} as c =>
            // a b c, where 1) a < b > c or 2) a > b < c
            // 1) if a > c => we make a pair of b and c. Otherwise, we make a pair of a and b
            for (int i = 1; i < v.size()-1; ++i) {
                if (v[i-1] < v[i] && v[i+1] < v[i]) { // v[i-1] < v[i] > v[i+1]
                    return 1;
                } else if (v[i-1] > v[i] && v[i+1] > v[i]) { // v[i-1] > v[i] < v[i+1]
                    return 1;
                }
            }
            
            return -1;
}



int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0, n = 0, counter = 0;
    ll tmp = 0;

    cin >> t;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        vector<ll> v;
        for (ll j = 0; j < n; ++j) {
            cin >> tmp;
            v.push_back(tmp);
        }

        if (isBeaut(v)) {
            cout << 0 << NL;
        } else {
            cout << ans(v) << NL;
        }
    }
}

#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

int main()
{
    // TODO: replace ints with lls
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    ll n = 0;
    cin >> n;
    if (n==1) {
        cout << "1" << NL;
        return 0;
    } else if (n <= 3) {
        cout << "NO SOLUTION" << NL;
        return 0;
    }

    vector<ll> v;

    // first place all odd number 
    for (ll i = 1; i <= n; i += 2) {
        v.push_back(i);
    }

    // then place all even numbers
    for (ll i = 2; i <= n; i += 2) {
        v.push_back(i);
    }

    // chapter 5.2 in CPH -- let the algo permulate slightly -- USING THE NEXT_PERMUTATION
    ll counter = 0;
    /*do {
        counter = 0;
        for (ll i = 1; i < n; ++i) {
            if (v[i] - v[i-1] == 1 || v[i-1] - v[i] == 1) {
                break;
            } else {
                ++counter;
            }
        }
    } while (counter < n-1 && next_permutation(v.begin(), v.end()));*/
    
    // WITHOUT THE NEXT_PERMUTATION
    do {
        for (ll i = 1; i < n; ++i) {
            if (v[i]-v[i-1] == 1 || v[i-1]-v[i] == 1) {
                // we can be sure that in this case v[i] and v[i-1] are in the middle, so v[i+1] isn't an overflow
                swap(v[i-1], v[0]);
                swap(v[i], v[n-1]);
                break;
            } else {
                ++counter;
            }
        }
    } while (counter < n-1);

    for (ll i = 0; i < n; ++i) {
        cout << v[i] << " ";
    }
    cout << NL;
}

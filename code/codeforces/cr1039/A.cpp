#include <iostream>
#include <bits/stdc++.h>

#define NL "\n";
typedef long long ll;

using namespace std;

void destroy(int index, vector<ll> &v) {
    v[index] = 0;
    for (int i = 0; i < v.size(); ++i)
        v[i] *= 2;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    
    int t = 0, n = 0, ans = 0;
    ll c = 0;
    cin >> t;

    ll tmp = 0;

    for (int i = 0; i < t; ++i) {
        cin >> n >> c;
        // scan
        vector<ll> v;
        for (int j = 0; j < n; ++j) {
            cin >> tmp;
            v.push_back(tmp);
        }

        sort(v.rbegin(), v.rend());
        

        if (v[v.size()-1] > c) {
            // all bags are expensive
            for (int i = 0; i < n; ++i) {
                if (v[i] != 0) {
                    destroy(i, v);
                    ++ans;
                }
            }
        } else {
            // first we need to destroy free bags
            // and we destroy those free bags, that are the most weighty
            for (int i = 0; i < n; ++i) {
                if (v[i] <= c && v[i] != 0)
                    destroy(i, v);
            }

            // then destroy expensive bags
            for (int i = 0; i < n; ++i) {
                if (v[i] != 0) {
                    destroy(i, v);
                    ++ans;
                }
            }

        }
        cout << ans << NL;
        ans = 0;
    }
}

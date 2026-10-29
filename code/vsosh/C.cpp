#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n = 0; cin >> n;
    vector<ll> a;
    ll tmp, total, eat = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        total += tmp;
        a.push_back(tmp);
    }

    sort(a.begin(), a.end(), greater<long long>());
    eat = total; // worst-case
    ll sum_of_kept = 0;

    for (int i = 0; i < n; ++i) {
        sum_of_kept = a[i-1];
        ll to_eat = total - (i*a[i-1]);
        if (to_eat < eat) {
            eat = to_eat;
        }
    }
    cout << eat << NL;
}

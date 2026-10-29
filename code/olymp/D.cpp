#include <bits/stdc++.h>

#define NL "\n"
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define INF 100000007
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    const int amount_of_unique_cards = 9;

    int n = 0; cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<int> p(amount_of_unique_cards, n), ans(n);

    for (int i = n-1; i >= 0; --i) {
        int c = (a[i][0]-'a')*3 + (a[i][1]-'1');
        p[c] = i;
        ans[i] = *max_element(all(p));
    }

    int t = 0; cin >> t;
    int l = 0, r = 0;
    for (int i = 0; i < t; ++i) {
        cin >> l >> r;
        l -= 1;
        r -= 1;

        if (ans[l] > r) {
            cout << -1 << NL;
        } else {
            cout << ans[l]-l+1 << NL;
        }
    }
}

#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0;
    cin >> n;
    set<int> a;
    int tmp = 0;
    bool is = false;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if (a.find(tmp) == a.end()) {
            a.insert(tmp);
        } else {
            if (!is)
                cout << "YES" << NL;
            is = true;
        }
    }

    if (!is)
        cout << "NO" << NL;
    return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
    int t = 0;
    cin >> t;
    while (t--) solve();
}

#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;
typedef bool boob;

using namespace std;

void solve() {
	int n = 0, tmp = 0;
    boob lock = false;
    cin >> n;
    vector<int> a;

    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        a.push_back(tmp);
    }

    sort(a.begin(), a.end());
/*    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << NL;*/

    for (int i = 0; i < n; ++i) {
        if (i%2==1 && i != n-1) { // kalamaki
            if (a[i] != a[i+1]) { // != means that a[i] < a[i+1], so if you swap them it is bad
                cout << "NO" << NL;
                lock = true;
                break;
            }
        }
    }

    if (!lock)
        cout << "YES" << NL;
}

int main()
{
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	int t = 0; cin >> t;
	while (t--) solve();
}


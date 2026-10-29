#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0, tmp = 0; cin >> n;
    bool zeros = false;
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if ((i == 0 || i == 1) && tmp == 0) {
            zeros = true;
        }
        a.push_back(tmp);
    }

    if (zeros) { // we don't need any operations
        cout << a[0] << NL;
        return;
    }
    
    if (n==2) { // n == 2 and the array isn't sorted, so we can just add a[0] to a[1]
        cout << a[0] + a[1] << NL;
        return;
    }

    a[0] = a[0] + a[1];
    a[1] = 0;
    cout << a[0] << NL;
    return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t = 0; cin >> t;
	while (t--) solve();
}


//////
#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

void solve() {
    int n = 0, m = 0;
    string a, b, c;
    cin >> n >> a >> m >> b >> c;
    string end = "", start = "";

    for (int i = 0; i < m; ++i) {
        if (c[i] == 'D') {
            end += b[i];
        } else if (c[i] == 'V') {
            start += b[i];
        }
    }

    reverse(start.begin(), start.end());

    cout << start << a << end << NL;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

    int t = 0;
    cin >> t;
    while (t--) solve();
}

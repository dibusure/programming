#include <algorithm>
#include <bits/stdc++.h>

#define NL "\n"
#define all(a) (a).begin(), (a).end()
#define INF 100000007
#define pb push_back
typedef long long ll;
using namespace std;

void solve() {
    int n = 0, c = 0;
    cin >> n >> c;
    vector<int> a(n, 0);
    vector<int> b(n, 0);

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    if (*min_element(all(a)) < *min_element(all(b))) {
        cout << "-1" << NL;
        return;
    }

    int time = 0;

    /*
     4 4
     4 5 2 3
     3 5 1 2

     with sort:
     2 3 4 5
     1 2 3 5

     with mind:
     4 2 3 5
     1 2 3 5

     c+3=7

     */


    if (!is_sorted(all(a))) {
        sort(all(a));
        time+=c;
    }

    // YOU CAN'T SORT B

    for (int i = 0; i < n; ++i) {
        time+=a[i]-b[i];
    }

    cout << time << NL;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 0; cin >> t;
    while (t--) solve();
}

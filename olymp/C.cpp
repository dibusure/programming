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
    int n = 0, t = 0; cin >> n;
    n *= 2;
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        a.pb(t);
    }

    sort(all(a));
    #ifdef DEBUG
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << NL;
    #endif
    int s = 0;

    for (int i = 0; i < n/2; ++i) {
        if (a[2*i+1] != a[2*i]) {
            s += a[2*i+1]-a[2*i]-1;
        }

        #ifdef DEBUG
        cout << "Pair " << a[2*i+1] << " and " << a[2*i] << NL;
        #endif
    }

    if (s < 0) {
        cout << 0 << NL;
    } else {
        cout << s << NL;
    }
}

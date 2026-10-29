#include <bits/stdc++.h>

#define NL "\n"
#define pb(a) push_back(a)
#define all(a) (a).begin(), (a).end()
#define INF 100000007
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N = 0;
    bool res = true;
    cin >> N;
    vector<int> table(N+1);

    for (int i = 1; i <= N; ++i)
        cin >> table[i];
    // so woodcutter 0 claims that he owns axe table[0] and so forth

    int woodcutter = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> woodcutter; // the goddess says that this woodcutter owns axe i
        if (table[woodcutter] != i)
            res = false;
    }

    if (res) {
        cout << "Yes" << NL;
    } else {
        cout << "No" << NL;
    }

}

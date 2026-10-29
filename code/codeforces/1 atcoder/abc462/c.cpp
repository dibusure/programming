#include <bits/stdc++.h>

#define NL "\n"
#define pb(a) push_back(a)
#define INF 100000007
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> X;
    vector<int> Y;
    int N = 0, x = 0, y = 0;

    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> x >> y;
        X.pb(x);
        Y.pb(y);
    }

    // because x, y is permutation of (1, ..., N)
    vector<int> table(N);
    for (int i = 0; i < N; ++i)
        table[X[i]] = Y[i];

    // so now we have a vector "sorted" by x
    // for concrete x there shouldn't be a point with less x and y, so we need to check only y
    int min_y = INF, res = 0;

    for (int i = 1; i <= N; ++i) {
        if (table[i] < min_y)
            res++;

        min_y = min(table[i], min_y);
    }

    cout << res << NL;
}

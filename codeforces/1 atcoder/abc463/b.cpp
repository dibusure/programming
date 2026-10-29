#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N = 0;
    char X = 0;
    bool res = false;
    string train = "";
    cin >> N >> X;

    for (int i = 0; i < N; ++i) {
        cin >> train;

        if (train[(int)(X-65)] == 'o') {
            res = true;
        }
    }

    if (res) {
        cout << "Yes" << NL;
    } else {
        cout << "No" << NL;
    }
}

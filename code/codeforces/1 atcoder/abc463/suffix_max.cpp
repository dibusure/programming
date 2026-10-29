#include <bits/stdc++.h>
#include <algorithm>

#define NL "\n"
typedef long long ll;
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N = 4;
    vector<int> H;
    H = {31, 26, 3, 15};

    vector<int> suffixMax(N + 1, 0);

    for (int i = N - 1; i >= 0; --i) {
        suffixMax[i] = max(suffixMax[i + 1], H[i]);
        for (int i = 0; i < N+1; ++i)
            cout << suffixMax[i] << " ";
        cout << NL;
    }
}

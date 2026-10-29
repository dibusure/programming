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
    string S = "";
    cin >> S;
    int e = 0, w = 0;
    for (int i = 0; i < S.length(); ++i) {
        if (S[i] == 'E') {
            e++;
        } else if (S[i] == 'W') {
            w++;
        }
    }

    if (e>w) {
        cout << "East" << NL;
    } else {
        cout << "West" << NL;
    }
}

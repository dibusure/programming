#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;
using namespace std;

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);

    if (b==0)
        return a;
    else
        return gcd(b, a-b);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int y = 0;
    int w = 0;
    int res = 0;
    cin >> y >> w;
    if (y >= w) {
        res = 6 - y + 1;
    } else {
        res = 6 - w + 1;
    }

    int a = gcd(res, 6);
    if (a == 1){
        cout << res << "/" << 6 << NL;
    } else {
        cout << res/a <<  "/" << 6/a << NL;
    }
}

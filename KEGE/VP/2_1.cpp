#include <bits/stdc++.h>

#define NL "\n"
typedef long long ll;

using namespace std;

int main()
{
    ll n = 0;
    cin >> n;
    if (((double)n)/7 > 1) {
       // cout << floor(n/7)*2 << " выходных" << NL;
        n -= (floor(n/7))*2; // без выходных
    }
    // s = ((2*a_1 + d(n-1)) / 2) * n
    cout << ((n+1)*n)/2 << NL;
}
